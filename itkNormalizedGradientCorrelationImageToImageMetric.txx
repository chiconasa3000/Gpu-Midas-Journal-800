
#ifndef __itkNormalizedGradientCorrelationImageToImageMetric_txx
#define __itkNormalizedGradientCorrelationImageToImageMetric_txx

#include "itkNormalizedGradientCorrelationImageToImageMetric.h"
#include <itkImageRegionConstIteratorWithIndex.h>



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
  }


/**
 * Initialize
 */
  template <class TFixedImage, class TMovingImage>
  void NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
  ::Initialize(void) throw ( ExceptionObject )
  {
    // Initialise the base class
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

        /*operador gaussiano
      m_SobelOperators[dim].SetDirection( 0 );
      m_SobelOperators[dim].SetVariance( 8.0 );
      m_SobelOperators[dim].CreateDirectional();  */

      //cada sobel filtro como puntero es instanciado
      //debemos tener cuidado con el tipo de puntero
      
      //primero instanciamos el respector puntero al filtro sobel
      m_FixedSobelFilters[dim] = SobelFilterType::New();

      //m_FixedSobelFilters[dim]->SetInput( this->GetFixedImage() );
      
      this->ptrGpuInputImage = dynamic_cast< const GPUInputImage * >(this->GetFixedImage());

      //m_FixedSobelFilters[dim]->SetInput(this->ptrGpuInputImage);
      //imagetoimagefilter que asumo que usa el imagetoimagemetric
      //de acuerdo a los parametros de plantilla que recibe
      //se colocara el numero de imagenes requeridas tanto para la entrada
      //como para la salida

      //en este caso debemos buscar el origen de image to image metric

      //el numero que va al inicio del set input es el indice de la imagen
      //para este caso al ser set inputs independientes para cada filtro
      //se debe colocar el setnumberofrequiredinputs(numero de imagenes fijas)
      m_FixedSobelFilters[dim]->SetInput(dim,this->ptrGpuInputImage);

      m_FixedSobelFilters[dim]->SetOperator( m_SobelOperators[dim] );      
      
      //la funcion recibe un condicion que tiene como plantilla las imagenes normales de itk
      //pero sabemos que el filtro esta desplegado para las imagenes GPU
      m_FixedSobelFilters[dim]->OverrideBoundaryCondition(&m_FixedBoundaryCondition );
      //m_FixedSobelFilters[dim]->Update();
      m_FixedSobelFilters[dim]->GetOutput(dim)->SetRequestedRegion(this->GetFixedImageRegion() );
      //m_FixedSobelFilters[dim]->GetOutput()->UpdateBuffers();
      
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
        //primero instanciamos el filtro sobel del tipo de imagen
      m_MovingSobelFilters[dim] = SobelFilterType::New();
      
      this->ptrGpuOutputImage = dynamic_cast<const GPUOutputImage *>(m_ResampleImageFilter->GetOutput());

      m_MovingSobelFilters[dim]->SetInput(dim,this->ptrGpuOutputImage);

      m_MovingSobelFilters[dim]->SetOperator( m_SobelOperators[dim] );
      m_MovingSobelFilters[dim]->OverrideBoundaryCondition( &m_MovingBoundaryCondition );
      //m_MovingSobelFilters[dim]->Update();
      m_MovingSobelFilters[dim]->GetOutput(dim)->SetRequestedRegion(this->GetFixedImageRegion());
      //m_MovingSobelFilters[dim]->GetOutput()->UpdateBuffers();
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
    this->m_NumberOfPixelsCounted = 0;
    this->SetTransformParameters( parameters );

    for (unsigned int dim=0; dim<m_MaxDimension; dim++)
      {
        //Aqui es donde recien se aplica el filtro sobel por GPU
        //esto necesita del indice
      this->m_FixedSobelFilters[dim]->Update();
      this->m_MovingSobelFilters[dim]->Update();
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

      for( unsigned int dim=0; dim<m_MaxDimension; dim++ )
        {
          //consiguiendo la salida del filtro sobel por GPU
          //se modifica por indice
        fixedGradient[dim] = m_FixedSobelFilters[dim]->GetOutput(dim)->GetPixel(fixedIndex );
        movingGradient[dim] = m_MovingSobelFilters[dim]->GetOutput(dim)->GetPixel(fixedIndex );
        
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
  void
  NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
  ::GetDerivative( const TransformParametersType & parameters,
                   DerivativeType & derivative           ) const
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
    Value      = this->GetValue( parameters );
    this->GetDerivative( parameters, Derivative );
  }


/**
 * Set the parameters that define a unique transform
 */
  template <class TFixedImage, class TMovingImage>
  void
  NormalizedGradientCorrelationImageToImageMetric<TFixedImage,TMovingImage>
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
