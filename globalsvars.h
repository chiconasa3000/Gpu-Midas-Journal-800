#ifndef GLOBALSVARS_H
#define GLOBALSVARS_H
#include <itkImageToImageMetric.h>
// DataObject will be global in order to share with other classes
namespace  itk{
    extern DataObject ** inputsProcessObject;
}
//void printDataObject();

#endif // GLOBALSVARS_H
