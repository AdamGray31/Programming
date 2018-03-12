/******************************************************************************
Class:SoftwareRasteriser
Implements:Window
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description: Class to encapsulate the various rasterisation techniques looked
at in the course material.

This is the class you'll be modifying the most!

-_-_-_-_-_-_-_,------,
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Matrix4.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderObject.h"
#include "Common.h"
#include "Window.h"

#include <vector>

using std::vector;

struct BoundingBox {
	Vector2 topLeft;
	Vector2 bottomRight;
};

enum SampleState {
	SAMPLE_NEAREST,
	SAMPLE_BILINEAR,
	SAMPLE_MIPMAP_NEAREST,
	SAMPLE_MIPMAP_BILINEAR
};

class RenderObject;
class Texture;

class SoftwareRasteriser : public Window {
public:

	SoftwareRasteriser(uint width, uint height);
	~SoftwareRasteriser(void);

	void DrawObject(RenderObject*o);

	void ClearBuffers();
	void SwapBuffers();

	void SetViewMatrix(const Matrix4 &m) {
		viewMatrix = m;
		viewProjMatrix = projectionMatrix * viewMatrix;
	}

	void SetProjectionMatrix(const Matrix4 &m) {
		projectionMatrix = m;
		viewProjMatrix = projectionMatrix * viewMatrix;
	}

	static float ScreenAreaOfTri(const Vector4 &v0,
		const Vector4 &v1,
		const Vector4 &v2);
	
	void SwitchTextureFiltering() {
		if (texSampleState == SAMPLE_NEAREST) {
			texSampleState = SAMPLE_BILINEAR;
			std::cout << "using bilinear\n";
		}
		else if (texSampleState == SAMPLE_BILINEAR) {
			texSampleState = SAMPLE_MIPMAP_NEAREST;
			std::cout << "using mipmap nearest\n";
		}
		else if (texSampleState == SAMPLE_MIPMAP_NEAREST) {
			texSampleState = SAMPLE_MIPMAP_BILINEAR;
			std::cout << "using mipmap bilinear\n";
		}
		else {
			texSampleState = SAMPLE_NEAREST;
			std::cout << "using nearest\n";
		}
	}

	void SwitchTextureFiltering(SampleState sample) {
		texSampleState = sample;
		if (texSampleState == SAMPLE_NEAREST) {
			std::cout << "using bilinear\n";
		}
		else if (texSampleState == SAMPLE_BILINEAR) {
			std::cout << "using mipmap nearest\n";
		}
		else if (texSampleState == SAMPLE_MIPMAP_NEAREST) {
			std::cout << "using mipmap bilinear\n";
		}
		else {
			std::cout << "using nearest\n";
		}
	}

protected:
	
	Colour*	buffers[2];
	unsigned short*	depthBuffer;
	int	currentDrawBuffer;

	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
	Matrix4 textureMatrix;
	Matrix4	viewProjMatrix;
	Matrix4	portMatrix;
	Texture *currentTexture;

	Colour*	GetCurrentBuffer();

	SampleState texSampleState;

	virtual void Resize();

	void RasterisePointsMesh(RenderObject*o);
	void RasteriseLinesMesh(RenderObject*o);
	void RasteriseTriMesh(RenderObject*o);

	BoundingBox CalculateBoxForTri(const Vector4 & a, const Vector4 & b, const Vector4 & c);	

	inline void	ShadePixel(uint x, uint y, const Colour&c) {
		if (y >= screenHeight || y<0) {
			return;
		}
		if (x >= screenWidth || x<0) {
			return;
		}

		int index = (y * screenWidth) + x;

		buffers[currentDrawBuffer][index] = c;
	}

	inline void BlendPixel(uint x, uint y, const Colour &source) {
		if (y >= screenHeight || y < 0) {
			return;
		}
		if (x >= screenWidth || x < 0) {
			return;
		}

		int index = (y * screenWidth) + x;

		Colour &dest = buffers[currentDrawBuffer][index];
		unsigned char sFactor = source.a;
		unsigned char dFactor = (255 - source.a);

		dest.r = ((source.r * sFactor) + (dest.r * dFactor)) / 255;
		dest.g = ((source.g * sFactor) + (dest.g * dFactor)) / 255;
		dest.b = ((source.b * sFactor) + (dest.b * dFactor)) / 255;
		dest.a = ((source.a * sFactor) + (dest.a * dFactor)) / 255;
	}

	void RasteriseLine(const Vector4 &v0, const Vector4 &v1,
		const Colour &colA = Colour(255, 255, 255, 255), const Colour &colB = Colour(255, 255, 255, 255),
		const Vector3 &texA = Vector3(0, 0, 0), const Vector3 &texB = Vector3(1, 1, 1));

	void RasteriseTri(const Vector4 &v0, const Vector4 &v1, const Vector4 &v2,
		const Colour &c0 = Colour(), const Colour &c1 = Colour(), const Colour &c2 = Colour(),
		const Vector3 &t0 = Vector3(), const Vector3 &t1 = Vector3(), const Vector3 &t2 = Vector3());

	bool DepthFunc(int x, int y, float depthValue);

	void CalculateWeights(
		const Vector4 &a, const Vector4 &b,
		const Vector4 &c, const Vector4 &p,
		float &alpha, float &beta, float &gamma);


			
};


