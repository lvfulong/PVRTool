// PVRTool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "assert.h"
#include "stdint.h"
#include "string.h"
/*
pArgv[1] inputPath
pArgv[2] outputPath
pArgv[3] x
pArgv[4] y
pArgv[5] width
pArgv[6] height
*/
struct rect
{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

#include "PVRTexture.h"

int main(int iArgc, char* pArgv[])
{
    assert(iArgc == 7);
#ifdef DEBUG
    for (int i = 0; i < iArgc; i++)
    {
        printf(" %s \n", pArgv[i]);
    }
#endif
    pvrtexture::CPVRTexture inputTexture(pArgv[1]);
    pvrtexture::CPVRTexture outputTexture(inputTexture.getHeader(), inputTexture.getDataPtr());

    MetaDataBlock MetaBlock;
    MetaBlock.DevFOURCC = 0x4c415941;//LAYA
    MetaBlock.u32Key = 0;
    MetaBlock.u32DataSize = sizeof(rect);

    rect* pRect = new rect;
    pRect->x = strtol(pArgv[3], NULL, 0);
    pRect->y = strtol(pArgv[4], NULL, 0);
    pRect->width = strtol(pArgv[5], NULL, 0);
    pRect->height = strtol(pArgv[6], NULL, 0);
    MetaBlock.Data = (PVRTuint8*)pRect;

    outputTexture.addMetaData(MetaBlock);
    outputTexture.saveFile(CPVRTString(pArgv[2], strlen(pArgv[2])));
    return 0;
}

