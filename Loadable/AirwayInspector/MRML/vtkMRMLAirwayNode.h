/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __vtkMRMLAirwayNode_h
#define __vtkMRMLAirwayNode_h

// Markups includes
#include "vtkSlicerAirwayInspectorModuleMRMLExport.h"

#include "vtkImageData.h"
#include "vtkPolyData.h"

#include "vtkMRMLNode.h"
#include "vtkMRMLModelNode.h"

// VTK includes
#include <vtkSmartPointer.h>

class  VTK_SLICER_AIRWAYINSPECTOR_MODULE_MRML_EXPORT vtkMRMLAirwayNode : public vtkMRMLNode
{
public:
  static vtkMRMLAirwayNode *New();
  vtkTypeMacro(vtkMRMLAirwayNode,vtkMRMLNode);

  void PrintSelf(ostream& os, vtkIndent indent);

  virtual const char* GetIcon() {return "";};

  //--------------------------------------------------------------------------
  // MRMLNode methods
  //--------------------------------------------------------------------------

  virtual vtkMRMLNode* CreateNodeInstance();

  /// Read node attributes from XML file
  virtual void ReadXMLAttributes( const char** atts);

  /// Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  /// Write this node's information to a vector of strings for passing to a CLI,
  /// precede each datum with the prefix if not an empty string
  /// coordinateSystemFlag = 0 for RAS, 1 for LPS
  /// multipleFlag = 1 for the whole list, 1 for the first selected markup
  virtual void WriteCLI(std::vector<std::string>& commandLine,
                        std::string prefix, int coordinateSystem = 0,
                        int multipleFlag = 1);

  /// Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  ///
  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "Airway";};

  /// Description:
  /// String ID of the volume MRML node
  vtkSetStringMacro(VolumeNodeID);
  vtkGetStringMacro(VolumeNodeID);

  ///
  /// Get/Set for Point
  vtkSetVector3Macro(XYZ,double);
  vtkGetVectorMacro(XYZ,double,3);

  ///
  /// Get/Set for orientation
  vtkSetVector4Macro(OrientationWXYZ,double);
  vtkGetVectorMacro(OrientationWXYZ,double,4);
  //void SetOrientationWXYZFromMatrix4x4(vtkMatrix4x4 *mat);

  /// Get/Set Threshold
  vtkSetMacro(Threshold, int);
  vtkGetMacro(Threshold, int);

  // Description:
  // Reformat airway along airway long axis
  vtkBooleanMacro(Reformat,int);
  vtkSetMacro(Reformat,int);
  vtkGetMacro(Reformat,int);

  // Description:
  // Reformat airway along airway long axis
  vtkBooleanMacro(ComputeCenter,int);
  vtkSetMacro(ComputeCenter,int);
  vtkGetMacro(ComputeCenter,int);

  // Description:
  // Reformat airway along airway long axis
  vtkSetMacro(Resolution,double);
  vtkGetMacro(Resolution,double);

  // Description:
  // Axis computation model:
  // 0 = Hessian.
  // 1 = from vktPolyData line.
  // 2 = from Vector field in PolyData pointData.
  vtkSetMacro(AxisMode,int);
  vtkGetMacro(AxisMode,int);
  void SetAxisModeToHessian() {this->SetAxisMode(HESSIAN);};
  void SetAxisModeToPolyData() {this->SetAxisMode(POLYDATA);};
  void SetAxisModeToVector() {this->SetAxisMode(VECTOR);};

  // Description:
  // Reconstruction kernel from image
  // 0 = Smooth
  // 1 = Sharp
  vtkSetMacro(Reconstruction,int);
  vtkGetMacro(Reconstruction,int);
  void SetReconstructionToSmooth() {this->SetReconstruction(SMOOTH);};
  void SetReconstructionToSharp() {this->SetReconstruction(SHARP);};

  // Description:
  // Reconstruction method
  // 0 = FWHM
  // 1 = ZeroCrossing
  // 2 = PhaseCongruency
  // 3 = PhaseCongruencyMultipleKernels
  vtkSetMacro(Method,int);
  vtkGetMacro(Method,int);
  void SetMethodToFWHM() {this->SetMethod(FWHM);};
  void SetMethodToZeroCrossing() {this->SetMethod(ZeroCrossing);};
  void SetMethodToPhaseCongruency() {this->SetMethod(PhaseCongruency);};
  void SetMethodToPhaseCongruencyMultipleKernels() {this->SetMethod(PhaseCongruencyMultipleKernels);};

  // Description:
  // Save a png image with the airway segmentation results for quality control
  vtkBooleanMacro(SaveAirwayImage,int);
  vtkSetMacro(SaveAirwayImage,int);
  vtkGetMacro(SaveAirwayImage,int);

  // Description:
  // File prefix for the airway image
  vtkSetStringMacro(AirwayImagePrefix);
  vtkGetStringMacro(AirwayImagePrefix);

  vtkGetObjectMacro(AirwayImage, vtkImageData);
  vtkSetObjectMacro(AirwayImage, vtkImageData);

  vtkGetObjectMacro(InnerContour, vtkPolyData);
  vtkSetObjectMacro(InnerContour, vtkPolyData);

  vtkGetObjectMacro(OuterContour, vtkPolyData);
  vtkSetObjectMacro(OuterContour, vtkPolyData);

  vtkGetObjectMacro(Mean, vtkDoubleArray);
  vtkGetObjectMacro(Std, vtkDoubleArray);
  vtkGetObjectMacro(Min, vtkDoubleArray);
  vtkGetObjectMacro(Max, vtkDoubleArray);
  vtkGetObjectMacro(Ellipse, vtkDoubleArray);

  enum AxisMode { HESSIAN, POLYDATA, VECTOR};
  enum ReconstructionMode {SMOOTH, SHARP};
  enum Method { FWHM, ZeroCrossing, PhaseCongruency, PhaseCongruencyMultipleKernels};

protected:
  vtkMRMLAirwayNode();
  ~vtkMRMLAirwayNode();
  vtkMRMLAirwayNode(const vtkMRMLAirwayNode&);
  void operator=(const vtkMRMLAirwayNode&);

private:
  /// Data
  double XYZ[3];
  double OrientationWXYZ[4];
  double Threshold;
  char *VolumeNodeID;

  double Resolution;
  int    Reformat;
  int    AxisMode;
  int    ComputeCenter;
  int    Reconstruction;
  int    Method;
  double SegmentPercentage;
  int    SaveAirwayImage;
  char   *AirwayImagePrefix;

  vtkImageData *AirwayImage;
  vtkPolyData  *InnerContour;
  vtkPolyData  *OuterContour;
  vtkDoubleArray *Mean;
  vtkDoubleArray *Std;
  vtkDoubleArray *Min;
  vtkDoubleArray *Max;
  vtkDoubleArray *Ellipse;
};

#endif