#ifndef _FBO_HPP_
#define _FBO_HPP_

	bool IsRenderbufferEXT(unsigned int renderbuffer);
    void BindRenderbufferEXT(enum target, unsigned int renderbuffer);
    void DeleteRenderbuffersEXT(unsigned int n, const unsigned int *renderbuffers);
    void GenRenderbuffersEXT(unsigned int n, unsigned int *renderbuffers);

    void RenderbufferStorageEXT(enum target, enum internalformat,
                                unsigned int width, unsigned int height);

    void GetRenderbufferParameterivEXT(enum target, enum pname, int *params);

    bool IsFramebufferEXT(unsigned int framebuffer);
    void BindFramebufferEXT(enum target, unsigned int framebuffer);
    void DeleteFramebuffersEXT(unsigned int n, const unsigned int *framebuffers);
    void GenFramebuffersEXT(unsigned int n, unsigned int *framebuffers);

    enum CheckFramebufferStatusEXT(enum target);

    void FramebufferTexture1DEXT(enum target, enum attachment,
                                 enum textarget, unsigned int texture,
                                 int level);
    void FramebufferTexture2DEXT(enum target, enum attachment,
                                 enum textarget, unsigned int texture,
                                 int level);
    void FramebufferTexture3DEXT(enum target, enum attachment,
                                 enum textarget, unsigned int texture,
                                 int level, int zoffset);

    void FramebufferRenderbufferEXT(enum target, enum attachment,
                                    enum renderbuffertarget, unsigned int renderbuffer);

    void GetFramebufferAttachmentParameterivEXT(enum target, enum attachment,
                                                enum pname, int *params);

    void GenerateMipmapEXT(enum target);

#define FRAMEBUFFER_EXT                     0x8D40

#define RENDERBUFFER_EXT                    0x8D41

#define STENCIL_INDEX1_EXT                  0x8D46
#define STENCIL_INDEX4_EXT                  0x8D47
#define STENCIL_INDEX8_EXT                  0x8D48
#define STENCIL_INDEX16_EXT                 0x8D49

#define        RENDERBUFFER_WIDTH_EXT              0x8D42
#define        RENDERBUFFER_HEIGHT_EXT             0x8D43
#define        RENDERBUFFER_INTERNAL_FORMAT_EXT    0x8D44
#define        RENDERBUFFER_RED_SIZE_EXT           0x8D50
#define        RENDERBUFFER_GREEN_SIZE_EXT         0x8D51
#define        RENDERBUFFER_BLUE_SIZE_EXT          0x8D52
#define        RENDERBUFFER_ALPHA_SIZE_EXT         0x8D53
#define        RENDERBUFFER_DEPTH_SIZE_EXT         0x8D54
#define        RENDERBUFFER_STENCIL_SIZE_EXT       0x8D55

#define        FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT            0x8CD0
#define        FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT            0x8CD1
#define        FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT          0x8CD2
#define        FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT  0x8CD3
#define        FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT     0x8CD4

#define        COLOR_ATTACHMENT0_EXT                0x8CE0
#define        COLOR_ATTACHMENT1_EXT                0x8CE1
#define        COLOR_ATTACHMENT2_EXT                0x8CE2
#define        COLOR_ATTACHMENT3_EXT                0x8CE3
#define        COLOR_ATTACHMENT4_EXT                0x8CE4
#define        COLOR_ATTACHMENT5_EXT                0x8CE5
#define        COLOR_ATTACHMENT6_EXT                0x8CE6
#define        COLOR_ATTACHMENT7_EXT                0x8CE7
#define        COLOR_ATTACHMENT8_EXT                0x8CE8
#define        COLOR_ATTACHMENT9_EXT                0x8CE9
#define        COLOR_ATTACHMENT10_EXT               0x8CEA
#define        COLOR_ATTACHMENT11_EXT               0x8CEB
#define        COLOR_ATTACHMENT12_EXT               0x8CEC
#define        COLOR_ATTACHMENT13_EXT               0x8CED
#define        COLOR_ATTACHMENT14_EXT               0x8CEE
#define        COLOR_ATTACHMENT15_EXT               0x8CEF
#define        DEPTH_ATTACHMENT_EXT                 0x8D00
#define        STENCIL_ATTACHMENT_EXT               0x8D20

#define        FRAMEBUFFER_COMPLETE_EXT                          0x8CD5
#define        FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT             0x8CD6
#define        FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT     0x8CD7
#define        FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT             0x8CD9
#define        FRAMEBUFFER_INCOMPLETE_FORMATS_EXT                0x8CDA
#define        FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT            0x8CDB
#define        FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT            0x8CDC
#define        FRAMEBUFFER_UNSUPPORTED_EXT                       0x8CDD

#define        FRAMEBUFFER_BINDING_EXT             0x8CA6
#define        RENDERBUFFER_BINDING_EXT            0x8CA7
#define        MAX_COLOR_ATTACHMENTS_EXT           0x8CDF
#define        MAX_RENDERBUFFER_SIZE_EXT           0x84E8

#define        INVALID_FRAMEBUFFER_OPERATION_EXT   0x0506

#endif