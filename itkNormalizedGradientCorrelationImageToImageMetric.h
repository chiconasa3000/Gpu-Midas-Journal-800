
#ifndef __itkNormalizedGradientCorrelationImageToImageMetric_h
#define __itkNormalizedGradientCorrelationImageToImageMetric_h

#include <itkImageToImageMetric.h>
#include <itkSobelOperator.h>
#include <itkNeighborhoodOperatorImageFilter.h>
#include <itkResampleImageFilter.h>

#include "itkGPUImage.h"
#include "itkGPUKernelManager.h"
#include "itkGPUContextManager.h"
#include "itkGPUImageToImageFilter.h"
#include "itkGPUNeighborhoodOperatorImageFilter.h"
#include "itkTimeProbe.h"
#include <itkNumericTraits.h>

namespace itk
{


/** \class NormalizedGradientCorrelationImageToImageMetric
 * \brief Computes the similarity between two images using the Normalized Gradient Correlation metric.
 *
 * This class computes the similarity between two images by calculation of the
 * normalised correlation between their gradients. Sobel filters are used to
 * calculate the images' gradients along the fixed image's dimensions. Then,
 * individual calculations are made for the correlations in each dimension,
 * which are finally summed (not averaged).
 *
 * As the Normalized Gradient Correlation metric estimates the images
 * similarity using the images' gradient rather than their direct intensities,
 * it is less sensitive to low-frequency signals such as the ones introduced
 * by soft tissue.
 *
 * The class should work for 2 and 3 dimensional images. In case that the
 * fixed image has 3 dimensions but a single slice, the number of used
 * dimensions will be reduced accordingly.
 *
 * References: G. P. Penney et al. A comparison of similarity measures for use
 * in 2-D-3-D medical image registration. IEEE Transactions on Medical Imaging.
 * 17(4):586-95. August 1998.
 *
 * \warning Please note that the original implementation of the metric
 * averages the calculations made on each dimension, but this implementation
 * only sums them.
 *
 */
template < class TFixedImage, class TMovingImage >
class ITK_EXPORT NormalizedGradientCorrelationImageToImageMetric :
public ImageToImageMetric< TFixedImage, TMovingImage>
{
public:

  /** Standard class typedefs. */
  typedef NormalizedGradientCorrelationImageToImageMetric Self;
  typedef ImageToImageMetric<TFixedImage, TMovingImage >  Superclass;

  typedef SmartPointer<Self>         Pointer;
  typedef SmartPointer<const Self>   ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(NormalizedGradientCorrelationImageToImageMetric, ImageToImageMetric);

/** Types transferred from the base class */
    typedef typename Superclass::RealType RealType;
// Work around a Visual Studio .NET bug
//#if defined(_MSC_VER) && (_MSC_VER == 1300)
//  typedef double RealType;
//#else
//  typedef typename Superclass::RealType                       RealType;
//#endif
  typedef typename Superclass::MovingImageType						MovingImageType;
  typedef typename Superclass::MovingImagePixelType					MovingImagePixelType;
  typedef typename Superclass::FixedImageType						FixedImageType;
  typedef typename FixedImageType::PixelType						FixedImagePixelType;

  itkStaticConstMacro(FixedImageDimension, unsigned int, TFixedImage::ImageDimension);
  typedef itk::Image<RealType, itkGetStaticConstMacro(FixedImageDimension)> GradientImageType;
	
  //para forma las imagenes de gpu solo se usa el tipo de pixel compartido en las imagenes normales de itk
  typedef GPUImage< FixedImagePixelType, itkGetStaticConstMacro(FixedImageDimension)> InputImageType;
  typedef GPUImage< RealType, itkGetStaticConstMacro(FixedImageDimension)> OutputImageType;
  
  //es correcto insertar como tipo la imagen de GPU
  typedef typename itk::GPUTraits< InputImageType >::Type  GPUInputImage;
  //peligro: se ha dado como tipo de imagen la miams de ingreso 
  //el vector de filtros sobel acepata el tipo de la imagen de entrada
  //esto da a entender que los tipos de las imagenes de salidas son solo
  //declaradas para los resultados y solo se definen.
  typedef typename itk::GPUTraits< InputImageType >::Type GPUOutputImage;


  //es correcto usar el pointer porque proviene de la clase GPUTraits
  //no se instancia ya que esta solo apuntara a lo que devuelva la conversion
   //typedef SmartPointer< Self >                                                   Pointer;
  //typedef SmartPointer< const Self >                                             ConstPointer;

  //typename GPUInputImage::ConstPointer ptrGpuInputImageDim1; 
  typename GPUInputImage::ConstPointer m_ptrosGPUInputImages[ itkGetStaticConstMacro( FixedImageDimension ) ];
  typename GPUOutputImage::ConstPointer m_ptrosGPUOutputImages[ itkGetStaticConstMacro( FixedImageDimension ) ];
  //typename GPUOutputImage::ConstPointer ptrGpuOutputImageDim1;
  //el pointer no es tuyo
  //typedef SmartPointer<GPUInputImage> myPointer;
  //typedef SmartPointer<const GPUInputImage> myConstPointer;
  //declarando el tipo de puntero
  //typename myPointer ptrGpuOutputImage;

  //typename  ptrGpuOutputImage;

  typedef RealType RealOutputPixelType;
  //el tipo de operador que proviene del tipo de pixel de la imagen de salida
  //debe provenir de la imagen de GPU
  typedef typename NumericTraits<RealOutputPixelType>::ValueType RealOutputPixelValueType;

  typedef ImageRegionConstIteratorWithIndex<FixedImageType>				FixedImageConstIteratorType;

  typedef typename Superclass::FixedImageConstPointer					FixedImageConstPointer;
  typedef typename Superclass::FixedImageRegionType					FixedImageRegionType;
  typedef typename FixedImageRegionType::SizeType                       		SizeType;
  typedef typename Superclass::TransformType						TransformType;
  typedef typename Superclass::TransformPointer						TransformPointer;
  typedef typename Superclass::TransformParametersType					TransformParametersType;
  typedef typename Superclass::TransformJacobianType					TransformJacobianType;

  typedef  typename Superclass::InterpolatorType    InterpolatorType;
  typedef  typename Superclass::InterpolatorPointer InterpolatorPointer;

  typedef typename Superclass::MeasureType      MeasureType;
  typedef typename Superclass::DerivativeType   DerivativeType;

  typedef typename Superclass::InputPointType   InputPointType;

  typedef itk::ResampleImageFilter< MovingImageType, FixedImageType >  ResampleImageFilterType;


  /** Get the derivatives of the match measure. */
  void GetDerivative( const TransformParametersType & parameters,
                            DerivativeType  & derivative ) const;

  /**  Get the value for single valued optimizers. */
  MeasureType GetValue( const TransformParametersType & parameters ) const;

  /**  Get value and derivatives for multiple valued optimizers. */
  void GetValueAndDerivative( const TransformParametersType & parameters,
                              MeasureType& Value, DerivativeType& derivative ) const;

  /** Initialize the Metric by making sure that all the components
   *  are present and plugged together correctly     */
  virtual void Initialize(void) throw ( ExceptionObject );

  /** Set/Get the value of Delta used for computing derivatives by finite
   * differences in the GetDerivative() method */
  itkSetMacro( DerivativeDelta, double );
  itkGetConstReferenceMacro( DerivativeDelta, double );

  /** Set the parameters defining the Transform. */
  void SetTransformParameters( const TransformParametersType & parameters ) const;

protected:
  NormalizedGradientCorrelationImageToImageMetric();
  virtual ~NormalizedGradientCorrelationImageToImageMetric() {};
  void PrintSelf(std::ostream& os, Indent indent) const;
  /**Define the neighbor operator filter byu GPU**/
  //este filtro debe ser desplegado para las imagenes por GPU
  typedef itk::GPUNeighborhoodOperatorImageFilter< InputImageType, OutputImageType, RealOutputPixelValueType > SobelFilterType;
  //typedef NeighborhoodOperatorImageFilter<FixedImageType, GradientImageType> SobelFilterType;

private:
  NormalizedGradientCorrelationImageToImageMetric(const Self&); //purposely not implemented
  void operator=(const Self&);                                  //purposely not implemented

  double  m_DerivativeDelta;
  unsigned int m_MaxDimension;

  /** The filter for transforming the moving images. */
  typename ResampleImageFilterType::Pointer m_ResampleImageFilter;
  
  /** Define the operator for the Neighboor Operator filter by GPU
  /** The Sobel gradients of the fixed image */
  SobelOperator< RealOutputPixelValueType, itkGetStaticConstMacro(FixedImageDimension) > m_SobelOperators[FixedImageDimension];
  //SobelOperator<RealType, itkGetStaticConstMacro(FixedImageDimension)> m_SobelOperators[FixedImageDimension];
 
  //Defines vectors of sobelOperator for every type of image
  typename SobelFilterType::Pointer m_FixedSobelFilters[ itkGetStaticConstMacro( FixedImageDimension ) ];
  typename SobelFilterType::Pointer m_MovingSobelFilters[ itkGetStaticConstMacro( FixedImageDimension ) ];

  //estas condiciones limitantes deben ser declaradas con las imagenes de GPU
  //en el filtro con operador gauss no se usaban estos tipos de cond
  ZeroFluxNeumannBoundaryCondition<InputImageType> m_FixedBoundaryCondition;
  ZeroFluxNeumannBoundaryCondition<InputImageType> m_MovingBoundaryCondition;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkNormalizedGradientCorrelationImageToImageMetric.txx"
#endif

#endif
