#pragma once

#include <glm/glm.hpp>

#include "SceneNode.hpp"
#include "Light.hpp"
#include "Image.hpp"
#include "Hit.hpp"
#include <vector>

void A5_Render(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters
		const glm::vec3 & ambient,
		const std::list<Light *> & lights,

		// Depth of Field Parameters
		float aperture,
		float focalLength,
		float screenPosition,

		// super sampling parameter
		int superSamplingScale
);

void rayIntersection(SceneNode * root, glm::vec3 origin, glm::vec3 dir,
												 Hit & hit);
void LoadTextures(SceneNode * root);
void LoadBumps(SceneNode * root);
void UniformDistribution(float c,int x,int y, Image &image1, Image &image2);
void superSampling(Image &image1, Image &image2, int scale);

glm::vec4 shade(SceneNode * root,
						const glm::vec3 origin,
						const glm::vec3 dir,
						const glm::vec3 ambient,
						const std::list<Light *> & lights,
						const int recursionDepth);

float Fresnel(float n1,float n2,glm::vec3 V,glm::vec3 &T, glm::vec3 N);
