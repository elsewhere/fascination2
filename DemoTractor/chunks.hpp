#ifndef _CHUNKS_
#define _CHUNKS_

//-------------------------------------------------------
//	Loader3DS enumerators
//-------------------------------------------------------

enum {
    CHUNK_RGBF      = 0x0010,
    CHUNK_RGBB      = 0x0011,
//    CHUNK_RBGB2     = 0x0012,       // ?? NOT HLS.

    CHUNK_PRJ       = 0xC23D,
    CHUNK_MLI       = 0x3DAA,

    CHUNK_MAIN      = 0x4D4D,
        CHUNK_OBJMESH   = 0x3D3D,
            CHUNK_BKGCOLOR  = 0x1200,
            CHUNK_AMBCOLOR  = 0x2100,
            CHUNK_OBJBLOCK  = 0x4000,
                CHUNK_TRIMESH   = 0x4100,
                    CHUNK_VERTLIST  = 0x4110,
                    CHUNK_FACELIST  = 0x4120,
                    CHUNK_FACEMAT   = 0x4130,
                    CHUNK_MAPLIST   = 0x4140,
                    CHUNK_SMOOLIST  = 0x4150,
                    CHUNK_TRMATRIX  = 0x4160,
                CHUNK_LIGHT     = 0x4600,
                    CHUNK_SPOTLIGHT = 0x4610,
                CHUNK_CAMERA    = 0x4700,
                CHUNK_HIERARCHY = 0x4F00,
        CHUNK_VIEWPORT  = 0x7001,
        CHUNK_MATERIAL  = 0xAFFF,
            CHUNK_MATNAME   = 0xA000,
            CHUNK_AMBIENT   = 0xA010,
            CHUNK_DIFFUSE   = 0xA020,
            CHUNK_SPECULAR  = 0xA030,
            CHUNK_TEXTURE   = 0xA200,
            CHUNK_BUMPMAP   = 0xA230,
            CHUNK_MAPFILE   = 0xA300,
        CHUNK_KEYFRAMER = 0xB000,
            CHUNK_AMBIENTKEY    = 0xB001,
            CHUNK_TRACKINFO = 0xB002,
                CHUNK_TRACKOBJNAME  = 0xB010,
                CHUNK_TRACKPIVOT    = 0xB013,
                CHUNK_TRACKPOS      = 0xB020,
                CHUNK_TRACKROTATE   = 0xB021,
                CHUNK_TRACKSCALE    = 0xB022,
                CHUNK_OBJNUMBER     = 0xB030,
            CHUNK_TRACKCAMERA = 0xB003,
                CHUNK_TRACKFOV  = 0xB023,
                CHUNK_TRACKROLL = 0xB024,
            CHUNK_TRACKCAMTGT = 0xB004,
            CHUNK_TRACKLIGHT  = 0xB005,
            CHUNK_TRACKLIGTGT = 0xB006,
            CHUNK_TRACKSPOTL  = 0xB007,
            CHUNK_FRAMES    = 0xB008,
};

#endif
