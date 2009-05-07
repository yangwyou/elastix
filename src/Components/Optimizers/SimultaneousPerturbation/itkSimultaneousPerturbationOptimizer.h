#ifndef __itkSimultaneousPerturbationOptimizer_h
#define __itkSimultaneousPerturbationOptimizer_h

#include "itkSingleValuedNonLinearOptimizer.h"


namespace itk
{
  
	/**
	 * \class SimultaneousPerturbationOptimizer
	 * \brief An optimizer based on simultaneous perturbation...
	 *
	 * \todo use the optimizer which is now in the ITK
	 * 
	 * This optimizer is an implementation of the Simultaneous
	 * Perturbation method, described in:
	 * 
	 * - http://www.jhuapl.edu/SPSA/
	 *
	 * - Spall, J.C. (1998), "An Overview of the Simultaneous
	 * Perturbation Method for Efficient Optimization," Johns
	 * Hopkins APL Technical Digest, vol. 19, pp. 482-492
 	 *
	 * \ingroup Optimizers
	 */
	
	class SimultaneousPerturbationOptimizer
		: public SingleValuedNonLinearOptimizer
	{
	public:
		
		/** Standard class typedefs. */
		typedef SimultaneousPerturbationOptimizer		Self;
		typedef SingleValuedNonLinearOptimizer			Superclass;
		typedef SmartPointer<Self>									Pointer;
		typedef SmartPointer<const Self>						ConstPointer;
		
		/** Method for creation through the object factory. */
		itkNewMacro( Self );
		
		/** Run-time type information (and related methods). */
		itkTypeMacro( SimultaneousPerturbationOptimizer, SingleValuedNonLinearOptimizer );
		
		/** Codes of stopping conditions */
		typedef enum {
			MaximumNumberOfIterations,
				MetricError
		} StopConditionType;
		
		/** Methods to configure the cost function. */
		itkGetConstMacro( Maximize, bool );
		itkSetMacro( Maximize, bool );
		itkBooleanMacro( Maximize );
		bool GetMinimize( ) const
		{ return !m_Maximize; }
		void SetMinimize(bool v)
		{ this->SetMaximize(!v); }
		void MinimizeOn()
		{ this->MaximizeOff(); }
		void MinimizeOff()
		{ this->MaximizeOn(); }
		
		/** Advance one step following the gradient direction. */
		virtual void AdvanceOneStep( void );
		
		/** Start optimization. */
		void StartOptimization( void );
		
		/** Resume previously stopped optimization with current parameters
		* \sa StopOptimization. */
		void ResumeOptimization( void );
		
		/** Stop optimization.
		* \sa ResumeOptimization */
		void StopOptimization( void );
		
		
		/** Set the number of iterations. */
		itkSetMacro( NumberOfIterations, unsigned long );
		
		/** Get the number of iterations. */
		itkGetConstMacro( NumberOfIterations, unsigned long );
		
		/** Get the current iteration number. */
		itkGetConstMacro( CurrentIteration, unsigned long );
		
		/** Get the current value. */
		itkGetConstMacro( Value, double );
		
		/** Get Stop condition. */
		itkGetConstMacro( StopCondition, StopConditionType );
		
		/** Set/Get a. */
		itkSetMacro( Param_a, double );
		itkGetMacro( Param_a, double );
		
		/** Set/Get c. */
		itkSetMacro( Param_c, double );
		itkGetMacro( Param_c, double );
		
		/** Set/Get A. */
		itkSetMacro( Param_A, double );
		itkGetMacro( Param_A, double );
		
		/** Set/Get alpha. */
		itkSetMacro( Param_alpha, double );
		itkGetMacro( Param_alpha, double );
		
		/** Set/Get gamma. */
		itkSetMacro( Param_gamma, double );
		itkGetMacro( Param_gamma, double );
		
		itkGetConstMacro( ComputeCurrentValue, bool );
		itkSetMacro( ComputeCurrentValue, bool );
		itkBooleanMacro( ComputeCurrentValue );
		
		
		/** Get the CurrentStepLength, GradientMagnitude and LearningRate (a_k) */
		itkGetConstMacro( CurrentStepLength, double );
		itkGetConstMacro( GradientMagnitude, double );
		itkGetConstMacro( LearningRate, double);
		
	protected:

		SimultaneousPerturbationOptimizer();
		virtual ~SimultaneousPerturbationOptimizer() {};

		/** PrintSelf method.*/
		void PrintSelf( std::ostream& os, Indent indent ) const;
		
		// made protected so subclass can access
		DerivativeType                m_Gradient; 
		bool                          m_Maximize;
		double												m_CurrentStepLength;
		double												m_LearningRate;
		double												m_GradientMagnitude;
		
		/** Boolean that says if the current value of
		* the metric has to be computed. This is not 
		* necessary for optimisation; just nice for
		* progress information.
		*/ 
		bool													m_ComputeCurrentValue;
		
		// Functions to compute the parameters at iteration k.
		virtual double Compute_a( unsigned long k ) const;
		virtual double Compute_c( unsigned long k ) const;
		
		//Function to Generate the perturbation vector.
		virtual void GenerateDelta( const unsigned int spaceDimension );
		
	private:

		SimultaneousPerturbationOptimizer( const Self& );	// purposely not implemented
		void operator=( const Self& );										// purposely not implemented
		
		/** Private member variables.*/
		bool                          m_Stop;
		double                        m_Value;
		StopConditionType             m_StopCondition;
		unsigned long                 m_NumberOfIterations;
		unsigned long                 m_CurrentIteration;
		
		/**Parameters, as described by Spall.*/
		double												m_Param_a;
		double												m_Param_c;
		double												m_Param_A;
		double												m_Param_alpha;
		double												m_Param_gamma;
		
		DerivativeType								m_Delta;
		
	}; // end class SimultaneousPerturbationOptimizer


} // end namespace itk


#endif // end #ifndef __itkSimultaneousPerturbationOptimizer_h
