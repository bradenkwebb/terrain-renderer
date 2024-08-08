#pragma once
#ifndef HELLO_TRIANGLE_H
#define HELLO_TRIANGLE_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.hpp"

void helloTriangle(GLFWwindow* window, Camera* camera);

#endif