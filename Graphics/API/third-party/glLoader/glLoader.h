#include <Veritas/Definitions/Definitions.h>

#ifdef OPENGLES
    #define GL_GLEXT_PROTOTYPES
    #include <GLES/gl.h>
    #include <GLES/glext.h>
    #include <GLES/glplatform.h>

    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #include <GLES2/gl2platform.h>

    #define glDispatchCompute(...)
    #define GL_COMPUTE_SHADER 0
    #define GL_GEOMETRY_SHADER 0

    #define GL_TEXTURE_3D GL_TEXTURE_3D_OES
    #define glFramebufferTexture3D
    #define glTexImage3D

    #define glUniform1ui
    #define glUniform2uiv
    #define glUniform3uiv
    #define glUniform4uiv

    #ifdef GLEXT_IMPL
        #define GLEXT_EXTERNALIZE
        #define GLEXT_VALUE = 0
    #else
        #define GLEXT_EXTERNALIZE extern
        #define GLEXT_VALUE
    #endif
    GLEXT_EXTERNALIZE PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMG glFramebufferTexture2DMultisampleIMG_ext GLEXT_VALUE;
    #define glFramebufferTexture2DMultisampleIMG glFramebufferTexture2DMultisampleIMG_ext
#elif defined(DESKTOP)
    #define GLEW_STATIC
    #include <GL/glew.h>
#endif
