#ifndef __itkGradientDifferenceSingleImageToImageMetric_txx
#define __itkGradientDifferenceSingleImageToImageMetric_txx

#include "itkGradientDifferenceSingleImageToImageMetric.h"
#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkNumericTraits.h"

namespace itk
{

/**
 * Constructor
 */
template <class TFixedImage, class TMovingImage>
GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>
::GradientDifferenceSingleImageToImageMetric()
{
    m_ResampleImageFilter = 0;

    m_MaxDimension = FixedImageDimension;

    for (unsigned dim=0; dim < m_MaxDimension; dim++)
    {
        m_Variance[dim] = itk::NumericTraits<GradientPixelType>::Zero;
    }

    //This is an important value delta using in differences intervals
    this->m_DerivativeDelta = 0.001;
}


/**
 * Initialize
 */
template <class TFixedImage, class TMovingImage>
void GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>
::Initialize(void) throw ( ExceptionObject )
{
    //Initialise the base class
    Superclass::Initialize();

    //size of the fixed image
    SizeType size = this->GetFixedImageRegion().GetSize();

    //initiliazing the dimension (#number of axis) of the fixed image
    for (unsigned int dim=0; dim<FixedImageDimension; dim++)
    {
        if( size[dim] < 2 )
        {
            m_MaxDimension = dim;
            break;
        }
    }

    // Create the filter to resample the moving image
    // transform the moving image in the same size of the fixed image
    m_ResampleImageFilter = ResampleImageFilterType::New();
    m_ResampleImageFilter->SetTransform(    this->m_Transform );
    m_ResampleImageFilter->SetInterpolator( this->m_Interpolator );
    m_ResampleImageFilter->SetInput( this->m_MovingImage );
    m_ResampleImageFilter->SetDefaultPixelValue( 0 );
    m_ResampleImageFilter->SetSize( this->m_FixedImage->GetLargestPossibleRegion().GetSize() );
    m_ResampleImageFilter->SetOutputOrigin( this->m_FixedImage->GetOrigin() );
    m_ResampleImageFilter->SetOutputSpacing( this->m_FixedImage->GetSpacing() );
    m_ResampleImageFilter->SetOutputDirection( this->m_FixedImage->GetDirection() );
    m_ResampleImageFilter->GetOutput()->SetRequestedRegion( this->GetFixedImageRegion() );

    // Compute the gradient of the fixed image
    for (unsigned int dim=0; dim<m_MaxDimension; dim++)
    {
        //for every dimension we apply the filter sobel in the fixed image

        //preparing the sobel filter for every dimension
        m_SobelOperators[dim].SetRadius( 1 );
        m_SobelOperators[dim].SetDirection( dim );//in this we determine the dimension
        m_SobelOperators[dim].CreateDirectional();

        m_FixedSobelFilter[dim] = SobelFilterType::New();
        m_FixedSobelFilter[dim]->OverrideBoundaryCondition( &m_FixedBoundaryCondition );
        m_FixedSobelFilter[dim]->SetOperator( m_SobelOperators[dim] ); //add the sobel filter
        m_FixedSobelFilter[dim]->SetInput( this->m_FixedImage ); //insert the entire fixed image
        m_FixedSobelFilter[dim]->GetOutput()->SetRequestedRegion( this->GetFixedImageRegion() );
        m_FixedSobelFilter[dim]->Update(); //apply the sobel filter
    }

    //this function we don't know how to made (TODO)
    this->ComputeVariance();

    // Compute the gradient of the transformed moving image
    for (unsigned int dim=0; dim<m_MaxDimension; dim++)
    {
        //initialize sobel filter for every dimension in the moving image
        m_MovingSobelFilter[dim] = SobelFilterType::New();
        m_MovingSobelFilter[dim]->OverrideBoundaryCondition( &m_MovingBoundaryCondition );
        m_MovingSobelFilter[dim]->SetOperator( m_SobelOperators[dim] ); //we reuse the sobel operator
        m_MovingSobelFilter[dim]->SetInput( m_ResampleImageFilter->GetOutput() ); //get the transform moving image
        m_MovingSobelFilter[dim]->GetOutput()->SetRequestedRegion( this->GetFixedImageRegion() );
        m_MovingSobelFilter[dim]->Update(); //apply the sobel filter
    }

}


/**
 * PrintSelf
 */
template <class TFixedImage, class TMovingImage>
void GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
    Superclass::PrintSelf( os, indent );
    os << indent << "DerivativeDelta: " << this->m_DerivativeDelta << std::endl;
}


/**
 * Compute the gradient variances in each dimension.
 */
template <class TFixedImage, class TMovingImage>
void GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>
::ComputeVariance( void ) const
{
    unsigned long nPixels;
    GradientPixelType mean[FixedImageDimension];

    for (unsigned int dim=0; dim < m_MaxDimension; dim++)
    {

        typedef itk::ImageRegionConstIteratorWithIndex<GradientImageType > IteratorType;
        IteratorType iterate( m_FixedSobelFilter[dim]->GetOutput(),this->GetFixedImageRegion() );

        // Calculate the gradients' mean first, and their range.
        nPixels =  0;

        mean[dim] = itk::NumericTraits<GradientPixelType>::Zero;

        //compute the mean for every dimension of the information in the pixel
        for ( iterate.GoToBegin(); !iterate.IsAtEnd(); ++iterate )
        {
            InputPointType inputPoint;
            this->m_FixedImage->TransformIndexToPhysicalPoint( iterate.GetIndex(), inputPoint );
            if( this->m_FixedImageMask && !this->m_FixedImageMask->IsInside( inputPoint ) )
            {
                continue;
            }

            mean[dim] += iterate.Get();
            nPixels++;
        }

        if (nPixels > 1)
        {
            mean[dim] /= nPixels;
        }
        else
        {
            itkExceptionMacro(<<"Insufficient pixels for mean and variance calculations");
        }

        // Now calculate the variance
        m_Variance[dim] = itk::NumericTraits<GradientPixelType>::Zero;
        GradientPixelType gradient;


        for ( iterate.GoToBegin(); !iterate.IsAtEnd(); ++iterate )
        {
            InputPointType inputPoint;
            this->m_FixedImage->TransformIndexToPhysicalPoint( iterate.GetIndex(), inputPoint );

            if( this->m_FixedImageMask && !this->m_FixedImageMask->IsInside( inputPoint ) )
            {
                continue;
            }

            //we remove the mean for every information pixel
            gradient = iterate.Get();
            gradient -= mean[dim];

            //finally this rest of information of pixel is multiply by the self
            //this is the variance
            m_Variance[dim] += gradient*gradient;
        }

        //the variance is divide by number of the pixels
        //this is the variance normalized
        m_Variance[dim] /= ( nPixels - 1 );

    } //for (unsigned int dim=0; dim < m_MaxDimension; dim++)
}


/**
 * Get the value of the similarity measure
 */
template <class TFixedImage, class TMovingImage>
typename GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>::MeasureType
GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>
::GetValue( const TransformParametersType & parameters ) const
{
    //set the parameters of tranformation  (OJO)
    this->SetTransformParameters( parameters );

    //the moving image is updated
    m_ResampleImageFilter->Update();

    //is applied the moving image sobel
    for (unsigned int dim=0; dim < m_MaxDimension; dim++)
    {
        m_MovingSobelFilter[dim]->Update();
    }


    typedef  itk::ImageRegionConstIteratorWithIndex< FixedImageType > IteratorType;

    MeasureType val = NumericTraits< MeasureType >::Zero;

    this->m_NumberOfPixelsCounted = 0;

    IteratorType iter( this->m_FixedImage, this->GetFixedImageRegion() );

    //iterate all the fixed image
    for ( iter.GoToBegin(); !iter.IsAtEnd(); ++iter )
    {
        IndexType index = iter.GetIndex();

        //Check if the fixed image's point is inside the mask
        InputPointType inputPoint;
        this->m_FixedImage->TransformIndexToPhysicalPoint( index, inputPoint );

        if( this->m_FixedImageMask && !this->m_FixedImageMask->IsInside( inputPoint ) )
        {
            continue;
        }

        //iterate in every dimension of the fixed image
        for( unsigned int dim=0; dim<m_MaxDimension; dim++ )
        {
            if( m_Variance[dim] == itk::NumericTraits<GradientPixelType>::Zero )
            {
                continue;
            }

            //we work the result of the sobel filter of the fixed image ang catch every pixel
            //we apply the difference between fixed and moving image in every dimension
            GradientPixelType diff = m_FixedSobelFilter[dim]->GetOutput()->GetPixel( index ) - m_MovingSobelFilter[dim]->GetOutput()->GetPixel( index );

            //the metric value is the variance divide by the same variance but multiply by diff to square.
            val += m_Variance[dim] / ( m_Variance[dim] + diff * diff );
        }

        this->m_NumberOfPixelsCounted++;
    }

    if( this->m_NumberOfPixelsCounted == 0 )
    {
        itkExceptionMacro(<< "No pixels counted for metric calculation" );
    }

    return val;
}


/**
 * Get the Derivative Measure
 */
template < class TFixedImage, class TMovingImage>
void GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>
::GetDerivative( const TransformParametersType & parameters, DerivativeType & derivative ) const
{
    //we get the derivative from using the finite differences aproximation
    TransformParametersType testPoint;
    testPoint = parameters;

    const unsigned int numberOfParameters = this->GetNumberOfParameters();
    derivative = DerivativeType( numberOfParameters );

    for( unsigned int i=0; i<numberOfParameters; i++)
    {
        testPoint[i] -= this->m_DerivativeDelta;
        const MeasureType valuep0 = this->GetValue( testPoint );
        testPoint[i] += 2 * this->m_DerivativeDelta;
        const MeasureType valuep1 = this->GetValue( testPoint );
        derivative[i] = (valuep1 - valuep0 ) / ( 2 * this->m_DerivativeDelta );
        testPoint[i] = parameters[i];
    }
}


/**
 * Get both the match Measure and theDerivative Measure
 */
template <class TFixedImage, class TMovingImage>
void GradientDifferenceSingleImageToImageMetric<TFixedImage,TMovingImage>
::GetValueAndDerivative(const TransformParametersType & parameters, MeasureType & Value, DerivativeType  & Derivative) const
{
    //compute two values derivative of the gradient and the metric value(gradient)
    Value      = this->GetValue( parameters );
    this->GetDerivative( parameters, Derivative );
}

} // end namespace itk


#endif
