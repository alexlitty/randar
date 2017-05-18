#ifndef SWIG
#ifndef RANDAR_UTILITY_IQM_HPP
#define RANDAR_UTILITY_IQM_HPP

#define IQM_MAGIC "INTERQUAKEMODEL"
#define IQM_VERSION 2

#include <GL/glew.h>

enum
{
    IQM_POSITION     = 0,
    IQM_TEXCOORD     = 1,
    IQM_NORMAL       = 2,
    IQM_TANGENT      = 3,
    IQM_BLENDINDEXES = 4,
    IQM_BLENDWEIGHTS = 5,
    IQM_COLOR        = 6,
    IQM_CUSTOM       = 0x10
};

enum
{
    IQM_BYTE   = 0,
    IQM_UBYTE  = 1,
    IQM_SHORT  = 2,
    IQM_USHORT = 3,
    IQM_INT    = 4,
    IQM_UINT   = 5,
    IQM_HALF   = 6,
    IQM_FLOAT  = 7,
    IQM_DOUBLE = 8
};

enum
{
    IQM_LOOP = 1<<0
};

namespace randar
{
    namespace iqm
    {
        struct header
        {
            char magic[16];
            unsigned int version;
            unsigned int filesize;
            unsigned int flags;
            unsigned int num_text, ofs_text;
            unsigned int num_meshes, ofs_meshes;
            unsigned int num_vertexarrays, num_vertexes, ofs_vertexarrays;
            unsigned int num_triangles, ofs_triangles, ofs_adjacency;
            unsigned int num_joints, ofs_joints;
            unsigned int num_poses, ofs_poses;
            unsigned int num_anims, ofs_anims;
            unsigned int num_frames, num_framechannels, ofs_frames, ofs_bounds;
            unsigned int num_comment, ofs_comment;
            unsigned int num_extensions, ofs_extensions;
        };

        struct mesh
        {
            unsigned int name;
            unsigned int material;
            unsigned int first_vertex, num_vertexes;
            unsigned int first_triangle, num_triangles;
        };

        struct triangle
        {
            unsigned int vertex[3];
        };

        struct adjacency
        {
            unsigned int triangle[3];
        };

        struct jointv1
        {
            unsigned int name;
            int parent;
            float translate[3], rotate[3], scale[3];
        };

        struct joint
        {
            unsigned int name;
            int parent;
            float translate[3], rotate[4], scale[3];
        };

        struct posev1
        {
            int parent;
            unsigned int mask;
            float channeloffset[9];
            float channelscale[9];
        };

        struct pose
        {
            int parent;
            unsigned int mask;
            float channeloffset[10];
            float channelscale[10];
        };

        struct anim
        {
            unsigned int name;
            unsigned int first_frame, num_frames;
            float framerate;
            unsigned int flags;
        };

        struct vertexarray
        {
            unsigned int type;
            unsigned int flags;
            unsigned int format;
            unsigned int size;
            unsigned int offset;
        };

        struct vertex
        {
            GLfloat position[3];
            GLfloat normal[3];
            GLfloat tangent[4];
            GLfloat texcoord[2];
            GLubyte blendindex[4];
            GLubyte blendweight[4];
        };

        struct bounds
        {
            float bbmin[3], bbmax[3];
            float xyradius, radius;
        };

        struct extension
        {
            unsigned int name;
            unsigned int num_data, ofs_data;
            unsigned int ofs_extensions; // pointer to next extension
        };

        static inline bool islittleendian() { union { int i; unsigned char b[sizeof(int)]; } conv; conv.i = 1; return conv.b[0] != 0; }
        inline unsigned short endianswap16(unsigned short n) { return (n<<8) | (n>>8); }
        inline unsigned int endianswap32(unsigned int n) { return (n<<24) | (n>>24) | ((n>>8)&0xFF00) | ((n<<8)&0xFF0000); }
        inline unsigned long long endianswap64(unsigned long long n) { return endianswap32((unsigned int)(n >> 32)) | ((unsigned long long)endianswap32((unsigned int)(n)) << 32); }
        template<class T> inline T endianswap(T n) { union { T t; unsigned int i; } conv; conv.t = n; conv.i = endianswap32(conv.i); return conv.t; }
        template<> inline unsigned char endianswap<unsigned char>(unsigned char n) { return n; }
        template<> inline char endianswap<char>(char n) { return n; }
        template<> inline unsigned short endianswap<unsigned short>(unsigned short n) { return endianswap16(n); }
        template<> inline short endianswap<short>(short n) { return endianswap16(n); }
        template<> inline unsigned int endianswap<unsigned int>(unsigned int n) { return endianswap32(n); }
        template<> inline int endianswap<int>(int n) { return endianswap32(n); }
        template<> inline unsigned long long endianswap<unsigned long long>(unsigned long long n) { return endianswap64(n); }
        template<> inline long long endianswap<long long>(long long n) { return endianswap64(n); }
        template<> inline double endianswap<double>(double n) { union { double t; unsigned int i; } conv; conv.t = n; conv.i = endianswap64(conv.i); return conv.t; }
        template<class T> inline void endianswap(T *buf, int len) { for(T *end = &buf[len]; buf < end; buf++) *buf = endianswap(*buf); }
        template<class T> inline T endiansame(T n) { return n; }
        template<class T> inline void endiansame(T *buf, int len) {}
        template<class T> inline T lilswap(T n) { return islittleendian() ? n : endianswap(n); }
        template<class T> inline void lilswap(T *buf, int len) { if(!islittleendian()) endianswap(buf, len); }
        template<class T> inline T bigswap(T n) { return islittleendian() ? endianswap(n) : n; }
        template<class T> inline void bigswap(T *buf, int len) { if(islittleendian()) endianswap(buf, len); }
    }
}

#endif
#endif
