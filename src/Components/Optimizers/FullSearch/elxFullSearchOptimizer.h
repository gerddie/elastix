/*======================================================================

  This file is part of the elastix software.

  Copyright (c) University Medical Center Utrecht. All rights reserved.
  See src/CopyrightElastix.txt or http://elastix.isi.uu.nl/legal.php for
  details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE. See the above copyright notices for more information.

======================================================================*/
#ifndef __elxFullSearchOptimizer_h
#define __elxFullSearchOptimizer_h

#include "elxIncludes.h" // include first to avoid MSVS warning
#include "itkFullSearchOptimizer.h"
#include <map>

#include "itkNDImageBase.h"

namespace elastix
{

/**
 * \class FullSearch
 * \brief An optimizer based on the itk::FullSearchOptimizer.
 *
 * Optimizer that scans a subspace of the parameter space
 * and searches for the best parameters.
 *
 * The results are written to the output-directory as an image
 * OptimizationSurface.\<elastixlevel\>.R\<resolution\>.mhd",
 * which is an N-dimensional float image, where N is the
 * dimension of the search space.
 *
 * The parameters used in this class are:
 * \parameter Optimizer: Select this optimizer as follows:\n
 *    <tt>(Optimizer "FullSearch")</tt>
 * \parameter FullSearchSpace\<r\>: Defines for resolution r a range of parameters to scan.\n
 *   Full syntax: (FullSearchSpace\<r\> \<parameter_name\> \<parameter_nr\> \<min\> \<max\> \<stepsize\> [...] ) \n
 *   example: <tt>(FullSearchSpace0 "translation_x" 2 -4.0 3.0 1.0 "rotation_y" 3 -1.0 1.0 0.5)</tt> \n
 *   This varies the second transform parameter in the range [-4.0 3.0] with steps of 1.0
 *   and the third parameter in the range [-1.0 1.0] with steps of 0.5. The names are used
 *   as column headers in the screen output.
 *
 * \ingroup Optimizers
 * \sa FullSearchOptimizer
 */

template< class TElastix >
class FullSearch :
  public
  itk::FullSearchOptimizer,
  public
  OptimizerBase< TElastix >
{
public:

  /** Standard ITK.*/
  typedef FullSearch                      Self;
  typedef itk::FullSearchOptimizer        Superclass1;
  typedef OptimizerBase< TElastix >       Superclass2;
  typedef itk::SmartPointer< Self >       Pointer;
  typedef itk::SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( FullSearch, itk::FullSearchOptimizer );

  /** Name of this class.
   * Use this name in the parameter file to select this specific optimizer. \n
   * example: <tt>(Optimizer "FullSearch")</tt>\n
   */
  elxClassNameMacro( "FullSearch" );

  /** Typedef's inherited from Superclass1.*/
  typedef Superclass1::CostFunctionType        CostFunctionType;
  typedef Superclass1::CostFunctionPointer     CostFunctionPointer;
  typedef Superclass1::ParametersType          ParametersType;
  typedef Superclass1::MeasureType             MeasureType;
  typedef Superclass1::ParameterValueType      ParameterValueType;
  typedef Superclass1::RangeValueType          RangeValueType;
  typedef Superclass1::RangeType               RangeType;
  typedef Superclass1::SearchSpaceType         SearchSpaceType;
  typedef Superclass1::SearchSpacePointer      SearchSpacePointer;
  typedef Superclass1::SearchSpaceIteratorType SearchSpaceIteratorType;
  typedef Superclass1::SearchSpacePointType    SearchSpacePointType;
  typedef Superclass1::SearchSpaceIndexType    SearchSpaceIndexType;
  typedef Superclass1::SearchSpaceSizeType     SearchSpaceSizeType;

  /** Typedef's inherited from Elastix.*/
  typedef typename Superclass2::ElastixType          ElastixType;
  typedef typename Superclass2::ElastixPointer       ElastixPointer;
  typedef typename Superclass2::ConfigurationType    ConfigurationType;
  typedef typename Superclass2::ConfigurationPointer ConfigurationPointer;
  typedef typename Superclass2::RegistrationType     RegistrationType;
  typedef typename Superclass2::RegistrationPointer  RegistrationPointer;
  typedef typename Superclass2::ITKBaseType          ITKBaseType;

  /** To store the results of the full search */
  typedef itk::NDImageBase< float >     NDImageType;
  typedef typename NDImageType::Pointer NDImagePointer;

  /** To store the names of the search space dimensions */
  typedef std::map< unsigned int, std::string >         DimensionNameMapType;
  typedef typename DimensionNameMapType::const_iterator NameIteratorType;

  /** Methods that have to be present everywhere.*/
  virtual void BeforeRegistration( void );

  virtual void BeforeEachResolution( void );

  virtual void AfterEachResolution( void );

  virtual void AfterEachIteration( void );

  virtual void AfterRegistration( void );

  /** \todo BeforeAll, checking parameters. */

  /** Get a pointer to the image containing the optimization surface. */
  itkGetObjectMacro( OptimizationSurface, NDImageType );

protected:

  FullSearch();
  virtual ~FullSearch() {}

  NDImagePointer m_OptimizationSurface;

  DimensionNameMapType m_SearchSpaceDimensionNames;

  /** Checks if an error generated while reading the search space
   * ranges from the parameter file is a real error. Prints some
   * error message if so.
   */
  //virtual int CheckSearchSpaceRangeDefinition(const std::string & fullFieldName,
  //  int errorcode, unsigned int entry_nr);
  virtual bool CheckSearchSpaceRangeDefinition( const std::string & fullFieldName,
    const bool found, const unsigned int entry_nr ) const;

private:

  FullSearch( const Self & );       // purposely not implemented
  void operator=( const Self & );   // purposely not implemented

};

} // end namespace elastix

#ifndef ITK_MANUAL_INSTANTIATION
#include "elxFullSearchOptimizer.hxx"
#endif

#endif // end #ifndef __elxFullSearchOptimizer_h
