#include "SoftwareRasteriser.h"
#include <cmath>
#include <math.h>
/*
While less 'neat' than just doing a 'new', like in the tutorials, it's usually
possible to render a bit quicker to use direct pointers to the drawing area
that the OS gives you. For a bit of a speedup, you can uncomment the define below
to switch to using this method.

For those of you new to the preprocessor, here's a quick explanation:

Preprocessor definitions like #define allow parts of a file to be selectively enabled
or disabled at compile time. This is useful for hiding parts of the codebase on a
per-platform basis: if you have support for linux and windows in your codebase, obviously
the linux platform won't have the windows platform headers available, so compilation will
fail. So instead you can hide away all the platform specific stuff:

#if PLATFORM_WINDOWS
 DoSomeWindowsStuff();
#elif PLATFORM_LINUX
 DoSomeLinuxStuff();
 #else
 #error Unsupported Platform Specified!
 #endif

 As in our usage, it also allows you to selectively compile in some different functionality
 without any 'run time' cost - if it's not enabled by the preprocessor, it won't make it to
 the compiler, so no assembly will be generated.

Also, I've implemented the Resize method for you, in a manner that'll behave itself
no matter which method you use. I kinda forgot to do that, so there was a chance you'd
get exceptions if you resized to a bigger screen area. Sorry about that.
*/
//#define USE_OS_BUFFERS



SoftwareRasteriser::SoftwareRasteriser(uint width, uint height)	: Window(width, height){
	currentTexture = NULL;
	currentDrawBuffer	= 0;
	texSampleState = SAMPLE_NEAREST;

#ifndef USE_OS_BUFFERS
	//Hi! In the tutorials, it's mentioned that we need to form our front + back buffer like so:
	for (int i = 0; i < 2; ++i) {
		buffers[i] = new Colour[screenWidth * screenHeight];
	}
#else
	//This works, but we can actually save a memcopy by rendering directly into the memory the 
	//windowing system gives us, which I've added to the Window class as the 'bufferData' pointers
	for (int i = 0; i < 2; ++i) {
		buffers[i] = (Colour*)bufferData[i];
	}
#endif

	depthBuffer		=	new unsigned short[screenWidth * screenHeight];

	float zScale	= (pow(2.0f,16) - 1) * 0.5f;

	Vector3 halfScreen = Vector3((screenWidth - 1) * 0.5f, (screenHeight - 1) * 0.5f, zScale);

	portMatrix = Matrix4::Translation(halfScreen) * Matrix4::Scale(halfScreen);
}

SoftwareRasteriser::~SoftwareRasteriser(void)	{
#ifndef USE_OS_BUFFERS
	for(int i = 0; i < 2; ++i) {
		delete[] buffers[i];
	}
#endif
	delete[] depthBuffer;
}

void SoftwareRasteriser::Resize() {
	Window::Resize(); //make sure our base class gets to do anything it needs to

#ifndef USE_OS_BUFFERS
	for (int i = 0; i < 2; ++i) {
		delete[] buffers[i];
		buffers[i] = new Colour[screenWidth * screenHeight];
	}
#else
	for (int i = 0; i < 2; ++i) {
		buffers[i] = (Colour*)bufferData[i];
	}
#endif

	delete[] depthBuffer;
	depthBuffer = new unsigned short[screenWidth * screenHeight];

	float zScale = (pow(2.0f, 16) - 1) * 0.5f;

	Vector3 halfScreen = Vector3((screenWidth - 1) * 0.5f, (screenHeight - 1) * 0.5f, zScale);

	portMatrix = Matrix4::Translation(halfScreen) * Matrix4::Scale(halfScreen);
}

Colour*	SoftwareRasteriser::GetCurrentBuffer() {
	return buffers[currentDrawBuffer];
}

void SoftwareRasteriser::ClearBuffers() {
	Colour* buffer = GetCurrentBuffer();

	unsigned int clearVal = 0xFF000000;
	unsigned int depthVal = ~0;

	for(uint y = 0; y < screenHeight; ++y) {
		for(uint x = 0; x < screenWidth; ++x) {
			buffer[(y * screenWidth) + x].c  = clearVal;
			depthBuffer[(y * screenWidth) + x] = depthVal;
		}
	}
}

void SoftwareRasteriser::SwapBuffers() {
	PresentBuffer(buffers[currentDrawBuffer]);
	currentDrawBuffer = !currentDrawBuffer;
}

void SoftwareRasteriser::DrawObject(RenderObject *o) {
	currentTexture = o->texture;
	switch (o -> GetMesh() -> GetType()) {
		case PRIMITIVE_POINTS: {
			RasterisePointsMesh(o);
		} break;
		case PRIMITIVE_LINES: {
			RasteriseLinesMesh(o);
		} break;
		case PRIMITIVE_TRIANGLES: {
			RasteriseTriMesh(o);
		}
	}

}

void SoftwareRasteriser::RasterisePointsMesh(RenderObject *o) {
	Matrix4 mvp = viewProjMatrix * o -> GetModelMatrix();

	for (uint i = 0; i < o -> GetMesh() -> numVertices; ++i) {
		Vector4 vertexPos = mvp * o -> GetMesh() -> vertices[i];
		vertexPos.SelfDivisionByW();
		
		Vector4 screenPos = portMatrix * vertexPos;
		ShadePixel((uint)screenPos.x, (uint)screenPos.y, Colour::White);
		
	}

}

void SoftwareRasteriser::RasteriseLinesMesh(RenderObject *o) {
	Matrix4 mvp = viewProjMatrix * o -> GetModelMatrix();
	
	for (uint i = 0; i < o -> GetMesh() -> numVertices; i += 2) {
		Vector4 v0 = mvp * o -> GetMesh() -> vertices[i];
		Vector4 v1 = mvp * o -> GetMesh() -> vertices[i + 1];
		
		v0.SelfDivisionByW();
		v1.SelfDivisionByW();

		Colour c0 = o->GetMesh()->colours[i];
		Colour c1 = o->GetMesh()->colours[i + 1];
		
		RasteriseLine(v0, v1, c0, c1);
		
	}
	
}

void SoftwareRasteriser::RasteriseTriMesh(RenderObject *o) {
	Matrix4 mvp = viewProjMatrix * o -> GetModelMatrix();
	
	Mesh * m = o -> GetMesh();

	for (uint i = 0; i < o -> GetMesh() -> numVertices; i += 3) {
	Vector4 v0 = mvp * o -> GetMesh() -> vertices[i];
	Vector4 v1 = mvp * o -> GetMesh() -> vertices[i + 1];
	Vector4 v2 = mvp * o -> GetMesh() -> vertices[i + 2];

		
	Vector3 t0 = Vector3(
		o -> GetMesh() -> textureCoords[i].x,
		o -> GetMesh() -> textureCoords[i].y, 1.0f) / v0.w;
			
	Vector3 t1 = Vector3(
		o -> GetMesh() -> textureCoords[i + 1].x,
		o -> GetMesh() -> textureCoords[i + 1].y, 1.0f) / v1.w;
	
	Vector3 t2 = Vector3(
		o -> GetMesh() -> textureCoords[i + 2].x,
		o -> GetMesh() -> textureCoords[i + 2].y, 1.0f) / v2.w;

	v0.SelfDivisionByW(); 
	v1.SelfDivisionByW(); 
	v2.SelfDivisionByW();
	RasteriseTri(v0, v1, v2,
		o->GetMesh()->colours[i],
		o->GetMesh()->colours[i + 1],
		o->GetMesh()->colours[i + 2],
		t0, t1, t2); // Ran out of space above sorry D:

	}
	
}

void SoftwareRasteriser::RasteriseLine(
	const Vector4 & vertA, const Vector4 & vertB,
	const Colour & colA, const Colour & colB,
	const Vector3 & texA, const Vector3 & texB) {
	// Transform our ndc coordinates to screen coordinates
	Vector4 v0 = portMatrix * vertA;
	Vector4 v1 = portMatrix * vertB;
	Vector4 dir = v1 - v0;// What direction is the line going ?
	
	int xDir = (dir.x < 0.0f) ? -1 : 1; // move left or right ?
	int yDir = (dir.y < 0.0f) ? -1 : 1; // move up or down ?
	
	int x = (int)v0.x; // Current x axis plot point
	int y = (int)v0.y; // Current y axis plot point
	
	int * target = NULL;// Increment on error overflow , x or y?
	int * scan = NULL;// Increment every iteration , x or y?
	int scanVal = 0;
	int targetVal = 0;
	
	float slope = 0.0f;
	
	int range = 0; // Bound our loop by this value ;
	// if we are steep , we have to scan over the y axis
	if (abs(dir.y) > abs(dir.x)) {
		slope = (dir.x / dir.y);
		range = (int)abs(dir.y);
		
		target = &x; // Error on x
		scan = &y; // Iterate over y
		scanVal = yDir;
		targetVal = xDir;
		
	}
	else { // not steep ? scan over the x axis ;
		slope = (dir.y / dir.x);
		range = (int)abs(dir.x);
		
		target = &y; // Error on y
		scan = &x; // Iterate over x
		scanVal = xDir;
		targetVal = yDir;
		
	}
	float absSlope = abs(slope);
	float error = 0.0f;
	
	float reciprocalRange = 1.0f / range;

	for (int i = 0; i < range; ++i) {
		float t = i*reciprocalRange;
		Colour currentCol = colB*t + colA * (1.0f - t);

		float zVal = v1.z*t + v0.z*(1.0f - t);

		
		if (DepthFunc((int)x, (int)y, zVal)) {
			ShadePixel(x, y, currentCol);
		}
		error += absSlope;

		if (error > 0.5f) {
			error -= 1.0f;
			(*target) += targetVal; // Either advance along x or y
		}
		(*scan) += scanVal; // Either iterate along x or y

	}


}

BoundingBox SoftwareRasteriser::CalculateBoxForTri(
	const Vector4 &a, const Vector4 &b, const Vector4 &c) {
	BoundingBox box;
	
	box.topLeft.x = a.x; // Start with the first vertex value
	box.topLeft.x = min(box.topLeft.x, b.x); // swap to second if less
	box.topLeft.x = min(box.topLeft.x, c.x); // swap to third if less
	box.topLeft.x = max(box.topLeft.x, 0.0f); // Screen Bound
	
	box.topLeft.y = a.y;
	box.topLeft.y = min(box.topLeft.y, b.y);
	box.topLeft.y = min(box.topLeft.y, c.y);
	box.topLeft.y = max(box.topLeft.y, 0.0f); // Screen Bound
	
	box.bottomRight.x = a.x; // Start with the first vertex value
	box.bottomRight.x = max(box.bottomRight.x, b.x); // swap if more
	box.bottomRight.x = max(box.bottomRight.x, c.x); // swap if more
	box.bottomRight.x = min(box.bottomRight.x, screenWidth); // Bound

	box.bottomRight.y = a.y;
	box.bottomRight.y = max(box.bottomRight.y, b.y);
	box.bottomRight.y = max(box.bottomRight.y, c.y);
	box.bottomRight.y = min(box.bottomRight.y, screenHeight); // Bound
	
	return box;
	
}

float SoftwareRasteriser::ScreenAreaOfTri(
	const Vector4 &a, const Vector4 &b, const Vector4 & c) {
	
		float area = ((a.x * b.y) + (b.x * c.y) + (c.x * a.y)) - //1st diagonals
		((b.x * a.y) + (c.x * b.y) + (a.x * c.y)); //2nd diagonals
	return area * 0.5f;
	
}

void SoftwareRasteriser::RasteriseTri(
	const Vector4 & triA, const Vector4 & triB, const Vector4 & triC,
	const Colour & colA, const Colour & colB, const Colour & colC,
	const Vector3 & texA, const Vector3 & texB, const Vector3 & texC) {
	// Incoming triangles are in NDC space
	Vector4 v0 = portMatrix * triA;// Now in viewport space !
	Vector4 v1 = portMatrix * triB;// Now in viewport space !
	Vector4 v2 = portMatrix * triC;// Now in viewport space !
	
	BoundingBox b = CalculateBoxForTri(v0, v1, v2);
	
	float triArea = ScreenAreaOfTri(v0, v1, v2);
	if (triArea < 0.0f) {
		return;
	}
	float areaRecip = 1.0f / abs(triArea);
	
	float subTriArea[3];
	Vector4 screenPos(0, 0, 0, 1);
	
	for (float y = b.topLeft.y; y < b.bottomRight.y; ++y) {
		for (float x = b.topLeft.x; x < b.bottomRight.x; ++x) {
			screenPos.x = x; // Create vertex ’p’
			screenPos.y = y; // Create vertex ’p’
			
			subTriArea[0] = abs(ScreenAreaOfTri(v0, screenPos, v1));
			subTriArea[1] = abs(ScreenAreaOfTri(v1, screenPos, v2));
			subTriArea[2] = abs(ScreenAreaOfTri(v2, screenPos, v0));
			
			float triSum = subTriArea[0] + subTriArea[1] + subTriArea[2];
			
			if (triSum >(triArea + 1.0f)) {
				continue;// current pixel is NOT IN this triangle !!
				
			}
			if (triSum < 1.0f) { // Tiny triangle we don ’t care about ...
				continue;
				
			}
			
			float alpha = subTriArea[1] * areaRecip;
			float beta = subTriArea[2] * areaRecip;
			float gamma = subTriArea[0] * areaRecip;

			float zVal = (v0.z*alpha) + (v1.z*beta) + (v2.z*gamma);

			if (!DepthFunc((int)x, (int)y, zVal)) {
				continue;
			}

			if (currentTexture) {// Texturing bit :
				// Interpolate in screen - linear space !
				Vector3 subTex = (texA * alpha) + (texB * beta) + (texC * gamma);
				// Convert the coordinates back into world - linear space !
				subTex.x /= subTex.z;
				subTex.y /= subTex.z;
				
				if (texSampleState == SAMPLE_BILINEAR) {
					ShadePixel((int)x, (int)y, currentTexture->BilinearTexSample(subTex));
				}
				else if (texSampleState == SAMPLE_NEAREST) {
					ShadePixel((int)x, (int)y, currentTexture->NearestTexSample(subTex));
				}
				else if (texSampleState == SAMPLE_MIPMAP_BILINEAR) {
					float xAlpha, xBeta, xGamma;
					float yAlpha, yBeta, yGamma;

					CalculateWeights(v0, v1, v2, screenPos + Vector4(1, 0, 0, 0),
						xAlpha, xBeta, xGamma);

					CalculateWeights(v0, v1, v2, screenPos + Vector4(0, 1, 0, 0),
						yAlpha, yBeta, yGamma);

					Vector3 xDerivs = (texA * xAlpha) + (texB * xBeta) + (texC * xGamma);
					Vector3 yDerivs = (texA * yAlpha) + (texB * yBeta) + (texC * yGamma);

					xDerivs.x /= xDerivs.z; // Return to a linear texture space
					xDerivs.y /= xDerivs.z;

					yDerivs.x /= yDerivs.z;
					yDerivs.y /= yDerivs.z;

					xDerivs = xDerivs - subTex; // Get the rate of change on x axis
					yDerivs = yDerivs - subTex; // Get the rate of change on y axis

												// We now have the rates of change on the x and y axis for tex u and v

					float maxU = max(abs(xDerivs.x), abs(yDerivs.x));
					float maxV = max(abs(xDerivs.y), abs(yDerivs.y));

					float maxChange = abs(max(maxU, maxV));

					int lambda = abs(log(maxChange) / log(2.0));
					// Sample from the usual texture coords , with new LOD
					ShadePixel((int)x, (int)y, currentTexture->BilinearTexSample(subTex, lambda));
				}
				else if (texSampleState == SAMPLE_MIPMAP_NEAREST) {
					float xAlpha, xBeta, xGamma;
					float yAlpha, yBeta, yGamma;
					
					CalculateWeights(v0, v1, v2, screenPos + Vector4(1, 0, 0, 0),
									xAlpha, xBeta, xGamma);
					
					CalculateWeights(v0, v1, v2, screenPos + Vector4(0, 1, 0, 0),
									yAlpha, yBeta, yGamma);
					
					Vector3 xDerivs = (texA * xAlpha) + (texB * xBeta) + (texC * xGamma);
					Vector3 yDerivs = (texA * yAlpha) + (texB * yBeta) + (texC * yGamma);
					
					xDerivs.x /= xDerivs.z; // Return to a linear texture space
					xDerivs.y /= xDerivs.z;
					
					yDerivs.x /= yDerivs.z;
					yDerivs.y /= yDerivs.z;
					
					xDerivs = xDerivs - subTex; // Get the rate of change on x axis
					yDerivs = yDerivs - subTex; // Get the rate of change on y axis
					
					// We now have the rates of change on the x and y axis for tex u and v
					
					float maxU = max(abs(xDerivs.x), abs(yDerivs.x));
					float maxV = max(abs(xDerivs.y), abs(yDerivs.y));
					
					float maxChange = abs(max(maxU, maxV));
					
					int lambda = abs(log(maxChange) / log(2.0));
					// Sample from the usual texture coords , with new LOD
					
					ShadePixel((int)x, (int)y, currentTexture -> NearestTexSample(subTex, lambda));

				}
				
			}
			else {
				Colour subColour = (
					(colA*alpha) +
					(colB*beta) +
					(colC*gamma));

				BlendPixel((uint)x, (uint)y, subColour);
			}
		}
		
	}

}

inline bool SoftwareRasteriser::DepthFunc(int x, int y, float depthValue) {
	if (y >= screenHeight || y < 0 || x >= screenWidth || x < 0) {
		return false;
	}
	
	int index = (y * screenWidth) + x;

	unsigned int castVal = (unsigned int)depthValue;

if (castVal > depthBuffer[index]) {
		return false;
	}
	depthBuffer[index] = castVal;
	return true;
}

void SoftwareRasteriser::CalculateWeights(
	const Vector4 &v0, const Vector4 &v1,
	const Vector4 &v2, const Vector4 &p,
	float &alpha, float &beta, float &gamma) {

	float triArea = ScreenAreaOfTri(v0, v1, v2);
	float areaRecip = 1.0f / triArea;

	float subTriArea[3];

	subTriArea[0] = abs(ScreenAreaOfTri(v0, p, v1));
	subTriArea[1] = abs(ScreenAreaOfTri(v1, p, v2));
	subTriArea[2] = abs(ScreenAreaOfTri(v2, p, v0));

	alpha	= subTriArea[1] * areaRecip;
	beta	= subTriArea[2] * areaRecip;
	gamma	= subTriArea[0] * areaRecip;

}