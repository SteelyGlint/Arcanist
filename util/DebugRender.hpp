#ifndef __DebugRender_hpp__
#define __DebugRender_hpp__
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>


template<typename T>
void print_texture_info(std::string fileName, T* pTexture)
{
	cout << "Image File: " << fileName << " ";
	print_texture_info(pTexture);
}

template<typename T>
void print_texture_info(T* pTexture)
{
	Uint32 format;
	int access;
	int width, height;

	if(SDL_QueryTexture(pTexture,&format,&access,&width,&height)<0)
		cout << "query texture error: " << SDL_GetError() << endl;
	else
	{
		cout << "Texture Info: " << std::dec << width << 'x' << height << ' ';
		if(access == SDL_TEXTUREACCESS_STATIC)
			cout << "(static) ";
		else if(access == SDL_TEXTUREACCESS_STREAMING)
			cout << "(streaming) ";
		if(SDL_ISPIXELFORMAT_INDEXED(format))
			cout << "(has palette) ";
		cout << SDL_GetPixelFormatName(format) << endl;
	}


	SDL_BlendMode blendmode;
	if(SDL_GetTextureBlendMode(pTexture,&blendmode) < 0)
		cout << "blend info error: " << SDL_GetError() << endl;
	else
	{
		cout << "Blend Mode: ";
		switch(blendmode)
		{
			case SDL_BLENDMODE_NONE:
				cout << "no blending" << endl;
				break;
			case SDL_BLENDMODE_BLEND:
				cout << "alpha blending" << endl;
				break;
			case SDL_BLENDMODE_ADD:
				cout << "additive blending" << endl;
				break;
			case SDL_BLENDMODE_MOD:
				cout << "color modulate" << endl;
				break;
			default:
				cout << "??? blending" << endl;
				break;
		}
	}


	Uint8 alpha;
	if(SDL_GetTextureAlphaMod(pTexture,&alpha) < 0)
		cout << "alpha info error: " << SDL_GetError() << endl;
	else
	{
		cout << "Alpha Mod #" << std::hex << (unsigned short) alpha << endl;
	}

	Uint8 r,g,b;
	if(SDL_GetTextureColorMod(pTexture,&r,&g,&b) < 0)
		cout << "color mod info error: " << SDL_GetError() << endl;
	else
	{
		cout << "Color Mod #" 
			<< std::hex << (unsigned short) r
			<< std::hex << (unsigned short) g
			<< std::hex << (unsigned short) b
			<< endl;
	}

}


template<typename T>
void print_render_info(T* renderer)
{
	SDL_RendererInfo r_info;
	if(SDL_GetRendererInfo(renderer, &r_info) < 0)
	{
		cout << "Invalid Render context: " << SDL_GetError() << endl;
		return;
	}

	cout << "Renderer " << r_info.name << endl;

	cout << "flags:";
	
	if(r_info.flags & SDL_RENDERER_SOFTWARE)
		cout << " software";
	if(r_info.flags & SDL_RENDERER_ACCELERATED)
		cout << " hardware accel";
	if(r_info.flags & SDL_RENDERER_PRESENTVSYNC)
		cout << " synchon with refresh rate";
	if(r_info.flags & SDL_RENDERER_TARGETTEXTURE)
		cout << " supports rendering to texture";
	
	cout << "\nMaximum texture width " << r_info.max_texture_width << " maximum texture height " << r_info.max_texture_height << std::endl;

	cout << "Render Formats:\n" << std::dec;
	unsigned int i;
	for(i = 0;i < r_info.num_texture_formats;++i)
	{
		cout << i << ": " << SDL_GetPixelFormatName(r_info.texture_formats[i]) << std::endl;
	}

}


#endif
