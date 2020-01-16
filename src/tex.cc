#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int32_t DWORD;
typedef int32_t UINT;
typedef int16_t WORD;

typedef enum {
	TF_DXT1			= 0, 
	TF_DXT5			= 1, 
	TF_RGB24		= 2, 
	TF_ARGB32		= 3, 
	TF_R5G6B5		= 4, 
	TF_A4R4G4B4		= 5, 
	TF_ACF          = 6,
	TF_UNKNOW		= 0xffffffff,
} TEXTUREFORMAT;

typedef struct {
	DWORD			dwSize;			//结构大小
	TEXTUREFORMAT	Format;			//文件格式
	UINT			dwDataSize;		//数据量大小
	UINT			dwWidth;		//宽
	UINT			dwHeight;		//高
	UINT			nMipMap;		//MipMap层数
	WORD			nExFrameCount;	//额外帧帧数
	WORD			nFrameCircle;	//帧周期
	DWORD			dwReserve[9];	//保留
} TEXTINFO;


char *LoadTex(const char * file, int *size) {
    FILE *fp = fopen(file, "r");
    
    DWORD res, version;
    fread(&res, sizeof(res), 1, fp);
    fread(&version, sizeof(version), 1, fp);

    TEXTINFO header;
    fread(&header, sizeof(header), 1, fp);

    // 遍历帧
    fread(size, sizeof(*size), 1, fp);
    char *buf = (char *)malloc(*size);
    fread(buf, *size, 1, fp);
    return buf;
}