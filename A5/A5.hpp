#pragma once

#include <glm/glm.hpp>

#include "SceneNode.hpp"
#include "Light.hpp"
#include "Image.hpp"
#include "Hit.hpp"
#include <vector>
using namespace glm;

void A5_Render(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const vec3 & eye,
		const vec3 & view,
		const vec3 & up,
		double fovy,

		// Lighting parameters
		const vec3 & ambient,
		const std::list<Light *> & lights,

		// Depth of Field Parameters
		float aperture,
		float focalLength,
		float screenPosition,

		// super sampling parameter
		int superSamplingScale
);

void rayIntersection(SceneNode * root, vec3 origin, vec3 dir,
												 Hit & hit);
void LoadTextures(SceneNode * root);
void LoadBumps(SceneNode * root);
void UniformDistribution(float c,int x,int y, Image &image1, Image &image2);
void superSampling(Image &image1, Image &image2, int scale);
void SoftShadows(SceneNode * root, vec3 dir, float p, Hit hit, Light* light, vec3 &L);

vec4 shade(SceneNode * root,
						const vec3 origin,
						const vec3 dir,
						const vec3 ambient,
						const std::list<Light *> & lights,
						const int recursionDepth);

float Fresnel(float n1,float n2,vec3 V,vec3 &T, vec3 N);
