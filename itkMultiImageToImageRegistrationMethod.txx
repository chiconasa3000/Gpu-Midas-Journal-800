#ifndef __itkMultiImageToImageRegistrationMethod_txx
#define __itkMultiImageToImageRegistrationMethod_txx

#include "itkMultiImageToImageRegistrationMethod.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"
#include "stdio.h"
namespace itk
{

/**
 * Constructor
 */
template < typename TFixedImage, typename TMovingImage >
MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::MultiImageToImageRegistrationMethod()
{

    this->SetNumberOfRequiredOutputs( 1 );  // for the Transform
    this->SetNumberOfRequiredInputs( 3 );

    m_MovingImage  = 0; // has to be provided by the user.
    m_Transform    = 0; // has to be provided by the user.
    m_MultiMetric  = 0; // has to be provided by the user.
    m_Optimizer    = 0; // has to be provided by the user.

    //allocate
    m_InitialTransformParameters = ParametersType(1);
    m_LastTransformParameters = ParametersType(1);

    //an initialization
    m_InitialTransformParameters.Fill( 0.0f );
    m_LastTransformParameters.Fill( 0.0f );

    //the decorator trasnform
    TransformOutputPointer transformDecorator = static_cast< TransformOutputType * >( this->MakeOutput(0).GetPointer() );

    //set the output of the moving image reusing the same index.
    this->ProcessObject::SetNthOutput( 0, transformDecorator.GetPointer() );

    //we can play with this
    this->SetNumberOfThreads( 1 );
    this->GetMultiThreader()->SetNumberOfThreads( this->GetNumberOfThreads() );
}


/**
 * GetMTime
 */
template < typename TFixedImage, typename TMovingImage >
unsigned long
MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::GetMTime() const
{
    //assign the maximum time in every process


    unsigned long mtime = Superclass::GetMTime();
    unsigned long m;

    //check the maximum time in every process.
    if (m_Transform)
    {
        m = m_Transform->GetMTime();
        mtime = (m > mtime ? m : mtime);
    }

    const unsigned int InterpTotal = m_MultiInterpolator.size();
    for ( unsigned int i=0; i<InterpTotal; i++ )
    {
        m = m_MultiInterpolator[i]->GetMTime();
        mtime = (m > mtime ? m : mtime);
    }

    if (m_MultiMetric)
    {
        m = m_MultiMetric->GetMTime();
        mtime = (m > mtime ? m : mtime);
    }

    if (m_Optimizer)
    {
        m = m_Optimizer->GetMTime();
        mtime = (m > mtime ? m : mtime);
    }

    const unsigned int FTotal = m_FixedMultiImage.size();
    for( unsigned int f=0; f<FTotal; f++ )
    {
        m = m_FixedMultiImage[f]->GetMTime();
        mtime = (m > mtime ? m : mtime);
    }


    if( m_FixedMultiImageMask.size() == FTotal )
    {
        for( unsigned int f=0; f<FTotal; f++ )
        {
            if( m_FixedMultiImageMask[f] )
            {
                m = m_FixedMultiImageMask[f]->GetMTime();
                mtime = (m > mtime ? m : mtime);
            }
        }
    }

    if (m_MovingImage)
    {
        m = m_MovingImage->GetMTime();
        mtime = (m > mtime ? m : mtime);
    }

    return mtime;

}


/*
 * Get the number of fixed images
 */
template < typename TFixedImage, typename TMovingImage >
const unsigned int
MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::GetNumberOfFixedImages() const
{
    //the size of the vector of the fixed images
    return m_FixedMultiImage.size();
}


/*
 * Set the initial transform parameters
 */
template < typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::SetInitialTransformParameters( const ParametersType & param )
{
    //initial transformation parameters
    m_InitialTransformParameters = param;
    this->Modified();
}


/**
 * Initialize by setting the interconnects between components.
 */
//initialize the registration
template < typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::Initialize() throw(ExceptionObject)
{
    //check moving image
    if( !m_MovingImage )
    {
        itkExceptionMacro(<<"MovingImage is not present");
    }


    const unsigned int FImgTotal = m_FixedMultiImage.size();

    //check size of fixed images
    if( FImgTotal == 0 )
    {
        itkExceptionMacro(<<"Fixed images' vector is empty.");
    }

    //check fixed images
    for( unsigned int fImg=0; fImg<FImgTotal; fImg++ )
    {
        if( !m_FixedMultiImage[fImg] )
        {
            itkExceptionMacro(<<"Fixed images' vector contains empty elements.");
        }
    }

    //check multi metric
    if ( !m_MultiMetric )
    {
        itkExceptionMacro(<<"MultiMetric object is not present" );
    }

    //check optimizer
    if ( !m_Optimizer )
    {
        itkExceptionMacro(<<"Optimizer is not present" );
    }

    //check transform
    if( !m_Transform )
    {
        itkExceptionMacro(<<"Transform is not present");
    }

    // Connect the transform to the Decorator.
    //the transform output is initialize
    TransformOutputType * transformOutput = static_cast< TransformOutputType * >( this->ProcessObject::GetOutput(0) );
    //this is setting by the transform variable
    transformOutput->Set( m_Transform.GetPointer() );

    // Check the array of interpolators
    const unsigned int InterpTotal = m_MultiInterpolator.size();
    if( InterpTotal != FImgTotal )
    {
        itkExceptionMacro(<<"Number of interpolators is not the same as the number of fixed images.");
    }

    //check interpolator
    for( unsigned int interp=0; interp<InterpTotal; interp++ )
    {
        if( !m_MultiInterpolator[interp] )
        {
            itkExceptionMacro(<<"Interpolators' vector contains empty element(s)");
        }
    }

    // Setup the regions
    if( m_FixedMultiImageRegion.size() == 0 )
    {
        for( unsigned int f=0; f<FImgTotal; f++ )
        {
            m_FixedMultiImageRegion.push_back( m_FixedMultiImage[f]->GetBufferedRegion() );
        }
    }
    else
    {
        //check regions
        if( m_FixedMultiImageRegion.size() != FImgTotal )
        {
            itkExceptionMacro( << "The number of regions must be equal to the "
                               << "number of fixed images" );
        }
    }

    // //check masks
    if( m_FixedMultiImageMask.size() > 0 && m_FixedMultiImageMask.size() != FImgTotal )
    {
        itkExceptionMacro(<<"Fixed images masks array has an incorrect number of "
                            "elements. Allowed values are 0 or the amount of fixed images");
    }

    //THE METRIC IS from itkMultiImageToImageMetric. It means from single value cost function
    //and use the macros in order to set multiples fixed images, regions and interpolators

    // Setup the metric
    //m_MultiMetric->DebugOn();
    m_MultiMetric->SetMovingImage( m_MovingImage );
    m_MultiMetric->SetFixedMultiImage( m_FixedMultiImage ); //vector of fixed images
    m_MultiMetric->SetTransform( m_Transform );
    m_MultiMetric->SetMultiInterpolator( m_MultiInterpolator );
    m_MultiMetric->SetFixedMultiImageRegion( m_FixedMultiImageRegion );
    m_MultiMetric->SetFixedMultiImageMask( m_FixedMultiImageMask );

    // Save the dataobjects from the process object
    saveDataObjectInputs();

    //inicialize the multi metric (OJO)
    m_MultiMetric->Initialize();

    //optimizer is from SingleValuedNonLinearOptimizer
    // Setup the optimizer with the multi metric (REOJO)
    m_Optimizer->SetCostFunction( m_MultiMetric );

    // Validate initial transform parameters (number of parameters)
    if ( m_InitialTransformParameters.Size() != m_Transform->GetNumberOfParameters() )
    {
        itkExceptionMacro(<<"Size mismatch between initial parameters and transform." <<
                          "Expected " << m_Transform->GetNumberOfParameters() << " parameters and received "
                          <<  m_InitialTransformParameters.Size() << " parameters");
    }

    //update the initial position with the new parameters of transformation
    m_Optimizer->SetInitialPosition( m_InitialTransformParameters );
}


/**
 * Starts the Optimization process
 */
template < typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::StartOptimization( void )
{
    try
    {
        //do the optimization
        m_Optimizer->StartOptimization();
    }

    catch( ExceptionObject& err )
    {
        // An error has occurred in the optimization.
        // Update the parameters
        m_LastTransformParameters = m_Optimizer->GetCurrentPosition();

        // Pass exception to caller
        throw err;
    }

    // get the results
    //this is the result of parameters and is setted in the m_Transform variable
    m_LastTransformParameters = m_Optimizer->GetCurrentPosition();
    m_Transform->SetParameters( m_LastTransformParameters );
}


/**
 * PrintSelf
 */
template < typename TFixedImage, typename TMovingImage >
void
MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
    Superclass::PrintSelf( os, indent );

    os << indent << "Moving image: " << m_MovingImage.GetPointer() << std::endl;
    for( unsigned int f=0; f<m_FixedMultiImage.size(); f++ )
    {
        os << indent << "FixedMultiImage[" << f << "]: ";
        os << m_FixedMultiImage[f].GetPointer() << std::endl;
    }

    os << indent << "Transform: " << m_Transform.GetPointer() << std::endl;
    os << indent << "MultiMetric: " << m_MultiMetric.GetPointer() << std::endl;
    os << indent << "Optimizer: " << m_Optimizer.GetPointer() << std::endl;

    for( unsigned int f=0; f<m_MultiInterpolator.size(); f++ )
    {
        os << indent << "MultiInterpolator[" << f << "]: ";
        os << m_MultiInterpolator[f].GetPointer() << std::endl;
    }

    for( unsigned int f=0; f<m_FixedMultiImageRegion.size(); f++ )
    {
        os << indent << "FixedMultiImageRegion[" << f << "]: ";
        os << m_FixedMultiImageRegion[f] << std::endl;
    }

    for( unsigned int f=0; f<m_FixedMultiImageMask.size(); f++ )
    {
        os << indent << "FixedMultiImageMask[" << f << "]: ";
        if( m_FixedMultiImageMask[f] )
        {
            os << m_FixedMultiImageMask[f].GetPointer() << std::endl;
        }
        else
        {
            os << "0" << std::endl;
        }
    }

    os << indent << "InitialTransformParameters: " << m_InitialTransformParameters << std::endl;
    os << indent << "LastTransformParameters: " << m_LastTransformParameters << std::endl;
}


/*
 * Generate Data
 */
template < typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::GenerateData()
{
    ParametersType empty(1);
    empty.Fill( 0.0 );
    try
    {
        // initialize the interconnects between components
        //call the initialize of the multi image regitration
        this->Initialize();
    }
    catch( ExceptionObject& err )
    {
        //if there exist an error the last paramaeters is set to null
        m_LastTransformParameters = empty;

        // pass exception to caller
        throw err;
    }
    //init the optimization (OJO)
    this->StartOptimization();
}


/**
 * Get Output
 */
template < typename TFixedImage, typename TMovingImage >
const typename MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>::TransformOutputType *
MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::GetOutput() const
{
    //El proceso obtiene del indice cero la imagen movible ya transformada
    return static_cast< const TransformOutputType * >( this->ProcessObject::GetOutput(0) );
}


/**
 * MakeOutput
 */
template < typename TFixedImage, typename TMovingImage >
DataObject::Pointer MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::MakeOutput(unsigned int output)
{
    switch (output)
    {
    case 0:
        //the special transform is returned by the object
        return static_cast<DataObject*>(TransformOutputType::New().GetPointer());
        break;
    default:
        itkExceptionMacro("MakeOutput request for an output number larger than the expected number of outputs");
        return 0;
    }
}


/**
 * AddFixedImage
 */

//add only one Fixed Image
template < typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::AddFixedImage( const FixedImageType* fixedImage )
{
    itkDebugMacro( "adding " << fixedImage << " to FixedMultiImage" );

    m_FixedMultiImage.push_back( fixedImage );

    // Always remeber that input number 0 is the moving image. Fixed images go from 1 onwards.
    //set begin from 1 to N fixed images
    this->ProcessObject::SetNthInput( m_FixedMultiImage.size(), const_cast<FixedImageType*>(fixedImage) );

    //modified is a flag i suppose (TODO)
    this->Modified();

}


/**
 * SetFixedMultiImage
 */
//add all vector of fixed images by newFixedMultiImage
template < typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::SetFixedMultiImage( const FixedMultiImageType newFixedMultiImage )
{
    itkDebugMacro( "setting FixedMultiImage" );

    if ( &m_FixedMultiImage != &newFixedMultiImage )
    {
        //Clear inputs
        const unsigned int OldFImgTotal = m_FixedMultiImage.size();
        for( unsigned int fImg=0; fImg<OldFImgTotal; fImg++ )
        {
            DataObject* oldFixedSingleImage = this->ProcessObject::GetInput( 1+fImg );
            this->ProcessObject::RemoveInput( oldFixedSingleImage );
        }

        //Then, set the new input images.
        this->m_FixedMultiImage = newFixedMultiImage;

        const unsigned int FImgTotal = m_FixedMultiImage.size();
        for( unsigned int fImg=0; fImg<FImgTotal; fImg++ )
        {
            const FixedImageType* fixedSingleImage = m_FixedMultiImage[fImg];
            //it set the correct index of the fixed image
            this->ProcessObject::SetNthInput(1+fImg, const_cast<FixedImageType*>(fixedSingleImage) );

        }
        this->Modified();
    }
}


/**
 * SetMovingImage
 */
template < typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage,TMovingImage>
::SetMovingImage( const MovingImageType * movingImage )
{
    //para mostrar la informacion de la imagen movible que se está seteando
    itkDebugMacro( "setting MovingImage to " << movingImage );

    if (this->m_MovingImage.GetPointer() != movingImage )
    {
        this->m_MovingImage = movingImage;

        // Process object is not const-correct so the const_cast is required here
        this->ProcessObject::SetNthInput(0, const_cast< MovingImageType *>( movingImage ) );
        this->Modified();
    }
}

template <typename TFixedImage, typename TMovingImage >
void MultiImageToImageRegistrationMethod<TFixedImage, TMovingImage>
::saveDataObjectInputs()
{
    const unsigned int inputsTotal = m_FixedMultiImage.size() + 1;
    DataObject ** inputs = new DataObject*[inputsTotal];
    for(int i=0; i<inputsTotal; i++){
        inputs[i] = this->ProcessObject::GetInput(i);
        //inputs[i][0].Print(std::cout);
    }
    m_MultiMetric->setInputsFromProcessObject(inputs);
}


} // end namespace itk


#endif
