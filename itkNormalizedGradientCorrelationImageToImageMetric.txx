
#ifndef __itkNormalizedGradientCorrelationImageToImageMetric_txx
#define __itkNormalizedGradientCorrelationImageToImageMetric_txx

#include "itkNormalizedGradientCorrelationImageToImageMetric.h"
#include <itkImageRegionConstIteratorWithIndex.h>
#include "globalsvars.h"
#include <stdio.h>
#include "itkImageDuplicator.h"
#include "itkImageRegionIterator.h"
#include "itkPasteImageFilter.h"

namespace itk
{

/**
 * Constructor
 */
template <class TFixedImage, class TMovingImage>
NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
::NormalizedGradientCorrelationImageToImageMetric()
{
    m_DerivativeDelta = 0.001;
    m_MaxDimension = FixedImageDimension;
    //void setImagesFromProcessObject();
}


/**
 * Initialize
 */
template <class TFixedImage, class TMovingImage>
void NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
::Initialize(void) throw ( ExceptionObject )
{
    // Initialise the base class (OJO)
    //necessary for fixed images and moving images
    //here we call getfixed image or getMovingImage and this function initialize both images
    //I must declare for GPUImageToImageMetric similarly
    Superclass::Initialize();

    SizeType size = this->GetFixedImageRegion().GetSize();
    for( unsigned int dim=0; dim < FixedImageDimension; dim++ )
    {
        if( size[dim] < 2 )
        {
            m_MaxDimension = dim;
            break;
        }
    }

    //para el error en tiempo de ejecucion de Input Primary is required  but not set
    //this->SetNumberOfRequiredInputs(2);

    for (unsigned int dim=0; dim<m_MaxDimension; dim++)
    {
        //el operador es sobel no es gaussiano
        m_SobelOperators[dim].SetRadius( 1 );
        m_SobelOperators[dim].SetDirection( dim );
        m_SobelOperators[dim].CreateDirectional();

        //cada sobel filtro como puntero es instanciado
        //debemos tener cuidado con el tipo de puntero

        typedef itk::Image< short, 3u >  ImageType;
        //imagen base que se instancia como imagen GPU
        ImageType::Pointer destImage = itk::GPUImage<short,3u>::New().GetPointer();
        //ImageType *image = itk::GPUImage<short,3u>::New();

        DataObject * dataSourceImage = &itk::inputsProcessObject[1][0];
        dataSourceImage->Print(std::cout);

        ImageType::Pointer sourceImage = ImageType::New();
        //copiando informacion de region de en la imagen destino
        sourceImage->CopyInformation(&itk::inputsProcessObject[1][0]);

        //Inicio de indice de pixel a partir de donde se copia
        ImageType::IndexType index;
        index[0] = 0;
        index[1] = 0;

        //la actualizacion con destImage copiando sus dimensiones de la sourceimage
        destImage->SetRegions(sourceImage->GetLargestPossibleRegion());
        destImage->Allocate();
        destImage->Update();

        //la fuente es actualizada despues de haber copiado la informacion
        sourceImage->Update();

        //usando el filtro
        using FilterType = itk::PasteImageFilter<ImageType, ImageType>;
        FilterType::Pointer filter = FilterType::New();
        //peligro con el getoutput
        filter->SetSourceImage(sourceImage);
        filter->SetSourceRegion(sourceImage->GetLargestPossibleRegion());
        filter->SetDestinationImage(destImage);
        filter->SetDestinationIndex(index);

        //considerando la parte de la imagen de destino
        //destImage->SetRegions(sourceImage->GetLargestPossibleRegion());
        //destImage->Allocate();
        //destImage->Update();

        //using WriterType = itk::ImageFileWriter< TFixedImage >;
        sourceImagef = WriterType::New();
        destImagef = WriterType::New();
        resultImagefFilter = WriterType::New();
        resultImagefGpu = WriterType::New();

        //Write source image
        sourceImagef->SetFileName("sourceImage.mha");
        sourceImagef->SetInput(sourceImage);
        sourceImagef->Update();

        //Write destiny image
        destImagef->SetFileName("destImage.mha");
        destImagef->SetInput(destImage);
        destImagef->Update();

        //Write the result from filter
        resultImagefFilter->SetFileName("resultImagefFilter.mha");
        resultImagefFilter->SetInput(destImage);
        resultImagefFilter->Update();

        //copiar la salida y guardar en la imagen destino
        ImageType::Pointer resultImage = itk::GPUImage<short,3u>::New().GetPointer();
        resultImage = filter->GetOutput();

        //Write the result gpu
        resultImagefGpu->SetFileName("resultImagefGpu.mha");
        resultImagefGpu->SetInput(destImage);
        resultImagefGpu->Update();

        //CONSEGUIR LA IMAGEN DESTINO

        /*
        typedef itk::ImageDuplicator< ImageType > DuplicatorType;
         DuplicatorType::Pointer duplicator = DuplicatorType::New();
         duplicator->SetInputImage(this->GetFixedImage());
         duplicator->Update();
         ImageType::Pointer clonedImage = duplicator->GetOutput();

        image->SetRegions(normalImage->GetLargestPossibleRegion());
        image->Allocate();



        itk::ImageRegionConstIterator<ImageType> inputIterator(normalImage, normalImage->GetLargestPossibleRegion());
        itk::ImageRegionIterator<ImageType> outputIterator(image, image->GetLargestPossibleRegion());

        while(!inputIterator.IsAtEnd())
        {
            outputIterator.Set(inputIterator.Get());
            ++inputIterator;
            ++outputIterator;
        }*/

        //Data object puesto a un puntero
        //DataObject * p = &itk::inputsProcessObject[1][0];

        //Copiar la data del dataObject a esta imagen especial
        //image->CopyInformation(p);

        m_ptrosGpuFixedImages[dim] = dynamic_cast< const itk::GPUImage<short,3u> *>(resultImage.GetPointer());
        //m_ptrosGpuFixedImages[dim] = dynamic_cast< const itk::GPUImage<short,3u> *>(p);
        m_FixedNeighborFilters[dim] = GpuMovingNeighboorFilterType::New();
        m_FixedNeighborFilters[dim]->OverrideBoundaryCondition(&m_FixedBoundaryCondition );
        m_FixedNeighborFilters[dim]->SetOperator( m_SobelOperators[dim] );
        //m_FixedSobelFilters[dim]->SetInput( this->GetFixedImage() );
        m_FixedNeighborFilters[dim]->SetInput(m_ptrosGpuFixedImages[dim]);
        m_FixedNeighborFilters[dim]->GetOutput()->SetRequestedRegion(this->GetFixedImageRegion() );
        //m_FixedNeighborFilters[dim]->GetOutput()->UpdateBuffers();

    }

    m_ResampleImageFilter = ResampleImageFilterType::New();

    m_ResampleImageFilter->SetTransform( this->m_Transform );
    m_ResampleImageFilter->SetInterpolator( this->m_Interpolator );
    m_ResampleImageFilter->SetInput( this->m_MovingImage );
    m_ResampleImageFilter->SetDefaultPixelValue(itk::NumericTraits<FixedImagePixelType>::Zero );
    m_ResampleImageFilter->UseReferenceImageOn();
    m_ResampleImageFilter->SetReferenceImage( this->m_FixedImage );
    m_ResampleImageFilter->GetOutput()->SetRequestedRegion(this->GetFixedImageRegion() );
    m_ResampleImageFilter->Update();

    for (unsigned int dim=0; dim < m_MaxDimension; dim++)
    {
        //std::cout<<"dimMoving: "<<dim<<std::endl;

        //primero instanciamos el filtro sobel del tipo de imagen
        m_ptrosGpuMovingImages[dim] = dynamic_cast<const GpuMovingImageType *>(m_ResampleImageFilter->GetOutput());
        m_MovingNeighborFilters[dim] = GpuMovingNeighboorFilterType::New();
        m_MovingNeighborFilters[dim]->OverrideBoundaryCondition( &m_MovingBoundaryCondition );
        m_MovingNeighborFilters[dim]->SetOperator( m_SobelOperators[dim] );
        m_MovingNeighborFilters[dim]->SetInput(m_ptrosGpuMovingImages[dim]);
        //m_MovingSobelFilters[dim]->Update();
        m_MovingNeighborFilters[dim]->GetOutput()->SetRequestedRegion(this->GetFixedImageRegion());
        m_MovingNeighborFilters[dim]->GetOutput()->UpdateBuffers();
    }
}


/**
 * PrintSelf
 */
template <class TFixedImage, class TMovingImage>
void
NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
    Superclass::PrintSelf( os, indent );
    os << indent << "DerivativeDelta: " << this->m_DerivativeDelta << std::endl;
}


/**
 * Get the value of the similarity measure
 */
template <class TFixedImage, class TMovingImage>
typename NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>::MeasureType
NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
::GetValue( const TransformParametersType & parameters ) const
{
    //this->Initialize();
    //in order to obtain the metric value we need the transformation parameters

    this->m_NumberOfPixelsCounted = 0;
    this->SetTransformParameters( parameters );

    for (unsigned int dim=0; dim<m_MaxDimension; dim++)
    {
        //Aqui es donde recien se aplica el filtro sobel por GPU
        this->m_FixedNeighborFilters[dim]->Update();
        this->m_MovingNeighborFilters[dim]->Update();
    }

    MeasureType val = NumericTraits< MeasureType >::Zero;

    /*
  cc: cross corrrelation
  fac: fixed auto correlation, this is, auto correlation of the fixed image
  mac: moving auto correlation, this is, moving image auto correlation
*/
    MeasureType cc[FixedImageDimension];
    MeasureType fac[FixedImageDimension];
    MeasureType mac[FixedImageDimension];

    for( unsigned int dim=0; dim < m_MaxDimension; dim++ )
    {
        cc[dim] = NumericTraits< MeasureType >::Zero;
        fac[dim] = NumericTraits< MeasureType >::Zero;
        mac[dim] = NumericTraits< MeasureType >::Zero;
    }

    //lo que recibe la salida es el tipo real RealType
    RealType movingGradient[FixedImageDimension];
    RealType fixedGradient[FixedImageDimension];

    FixedImageConstIteratorType iter( this->m_FixedImage, this->GetFixedImageRegion() );

    //traverse the fixed image
    for( iter.GoToBegin(); !iter.IsAtEnd(); ++iter )
    {
        typename FixedImageType::IndexType fixedIndex = iter.GetIndex();

        //Check if point is inside the fixed image mask
        InputPointType inputPoint;
        this->GetFixedImage()->TransformIndexToPhysicalPoint( fixedIndex, inputPoint );

        if( this->m_FixedImageMask && !this->m_FixedImageMask->IsInside( inputPoint ) )
        {
            continue;
        }

        //traverse for every dimension
        for( unsigned int dim=0; dim<m_MaxDimension; dim++ )
        {
            //consiguiendo la salida del filtro sobel por GPU
            fixedGradient[dim] = m_FixedNeighborFilters[dim]->GetOutput()->GetPixel(fixedIndex );
            movingGradient[dim] = m_MovingNeighborFilters[dim]->GetOutput()->GetPixel(fixedIndex );

            cc[dim] +=  movingGradient[dim] * fixedGradient[dim];
            fac[dim] += fixedGradient[dim] * fixedGradient[dim];
            mac[dim] += movingGradient[dim] * movingGradient[dim];
        }

        this->m_NumberOfPixelsCounted++;
    }

    if( this->m_NumberOfPixelsCounted == 0 )
    {
        itkExceptionMacro(<< "No voxels counted for metric calculation");
    }

    for( unsigned int dim=0; dim < m_MaxDimension; dim++ )
    {
        if( fac[dim] == NumericTraits< MeasureType >::Zero ||
                mac[dim] == NumericTraits< MeasureType >::Zero )
        {
            itkExceptionMacro(<< "Auto correlation(s) equal to zero");
        }
    }

    for( unsigned int dim=0; dim < m_MaxDimension; dim++ )
    {
        val += cc[dim] / vcl_sqrt( fac[dim] * mac[dim] ) / m_MaxDimension;
    }
    return val;
}


/**
 * Get the Derivative Measure
 */
template < class TFixedImage, class TMovingImage>
void NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
::GetDerivative( const TransformParametersType & parameters, DerivativeType & derivative ) const
{
    TransformParametersType testPoint;
    testPoint = parameters;

    const unsigned int numberOfParameters = this->GetNumberOfParameters();
    derivative = DerivativeType( numberOfParameters );

    for( unsigned int i=0; i<numberOfParameters; i++)
    {
        testPoint[i] -= this->m_DerivativeDelta;
        const MeasureType valuep0 = this->GetValue( testPoint );
        testPoint[i] += 2* this->m_DerivativeDelta;
        const MeasureType valuep1 = this->GetValue( testPoint );
        derivative[i] = (valuep1 - valuep0 ) / ( 2 * this->m_DerivativeDelta );
        testPoint[i] = parameters[i];
    }
}


/**
 * Get both the match Measure and theDerivative Measure
 */
template <class TFixedImage, class TMovingImage>
void
NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
::GetValueAndDerivative(const TransformParametersType & parameters,
                        MeasureType & Value, DerivativeType  & Derivative) const
{
    Value = this->GetValue( parameters );
    this->GetDerivative( parameters, Derivative );
}


/**
 * Set the parameters that define a unique transform
 */
template <class TFixedImage, class TMovingImage>
void NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
::SetTransformParameters( const TransformParametersType & parameters ) const
{
    if( !this->m_Transform )
    {
        itkExceptionMacro(<<"Transform has not been assigned");
    }
    this->m_Transform->SetParameters( parameters );
}

} // end namespace itk

#endif
