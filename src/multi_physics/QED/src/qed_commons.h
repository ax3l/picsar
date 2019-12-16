#ifndef PICSAR_MULTIPHYSICS_QED_COMMONS
#define PICSAR_MULTIPHYSICS_QED_COMMONS

//###################### Decorator to compile some functions for CPU and GPU####

    //This flag should be set by the user
    //e.g. #define PXRMP_GPU __host__ __device__

    //Breit-Wheeler and Quantum Synchrotrons engines offer the possibility
    //to include only the 'core functions' required for a simulation done on GPUs,
    //dropping everythin related to table generation. This allows avoiding
    //the Boost dependency.
    //#define PXRMP_CORE_ONLY

    #ifndef PXRMP_GPU
      #define PXRMP_INTERNAL_NO_GPU
      #define PXRMP_INTERNAL_GPU_DECORATOR
    #else
      #define PXRMP_INTERNAL_WITH_GPU
      #define PXRMP_INTERNAL_GPU_DECORATOR PXRMP_GPU
    #endif

    #ifdef PXRMP_INTERNAL_WITH_GPU
      #define PXRMP_INTERNAL_ENABLE_GPU_FRIENDLY_ARRAY
    #endif

    #ifdef PXRMP_FORCE_PICSAR_ARRAY
        #define PXRMP_INTERNAL_ENABLE_GPU_FRIENDLY_ARRAY
    #endif

    //Restrict qualifier (compiler specific!)
    #ifdef PXRMP_RESTRICT
      #define PXRMR_INTERNAL_RESTRICT PXRMP_RESTRICT
    #else
      #ifdef _WIN32
        #define PXRMR_INTERNAL_RESTRICT __restrict
      #else
        #define PXRMR_INTERNAL_RESTRICT __restrict__
      #endif
    #endif

    //Force inline pragmas (compiler specific!)
    #ifdef PXRMP_FORCE_INLINE
      #define PXRMP_INTERNAL_FORCE_INLINE_DECORATOR PXRMP_FORCE_INLINE
    #else
      #if defined(__CUDA_ARCH__)
        #define PXRMP_INTERNAL_FORCE_INLINE_DECORATOR __forceinline__
      #elif defined(__INTEL_COMPILER)
        #define PXRMP_INTERNAL_FORCE_INLINE_DECORATOR inline __attribute__((always_inline))
      #elif defined(__clang__)
        #define PXRMP_INTERNAL_FORCE_INLINE_DECORATOR inline __attribute__((always_inline))
      #elif defined(__GNUC__)
        #define PXRMP_INTERNAL_FORCE_INLINE_DECORATOR inline __attribute__((always_inline))
      #elif defined(__ibmxl__)
        #define PXRMP_INTERNAL_FORCE_INLINE_DECORATOR inline __attribute__((always_inline))
      #else
        #define PXRMP_INTERNAL_FORCE_INLINE_DECORATOR inline
      #endif
    #endif


    #ifdef PXRMP_RESTRICT_SET_DECORATOR
      #define PXRMP_INTERNAL_RESTRICT PXRMP_RESTRICT_SET_DECORATOR
    #else
      #define PXRMP_INTERNAL_RESTRICT __restrict__
    #endif


  #ifdef PXRMP_FORCE_BOOST_FOR_SPECFUNC
    #define PXRMP_INTERNAL_SPECFUNC_WITH_BOOST
  #else
    #if __cplusplus > 201402L
      #define PXRMP_INTERNAL_SPECFUNC_WITH_CXX17
    #else
      #define PXRMP_INTERNAL_SPECFUNC_WITH_BOOST
    #endif
  #endif

  #ifdef PXRMP_FORCE_PICSAR_UPPER_BOUND
    #define PXRMP_INTERNAL_PICSAR_UPPER_BOUND
  #else
    #ifdef PXRMP_INTERNAL_WITH_GPU
      #define PXRMP_INTERNAL_PICSAR_UPPER_BOUND
    #else
      #define PXRMP_INTERNAL_STL_UPPER_BOUND
    #endif
  #endif

//##############################################################################

#endif// PICSAR_MULTIPHYSICS_QED_COMMONS
