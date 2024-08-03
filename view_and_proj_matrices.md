### View Matrix

The **view matrix** is used to transform world coordinates to camera coordinates. It essentially represents the camera's position and orientation in the world.

In OpenGL, you can create a view matrix using the glm::lookAt function from the GLM library:

```cpp
glm::mat4 view = glm::lookAt(
    glm::vec3(cameraPos),  // Camera position in world space
    glm::vec3(targetPos),  // Target position the camera is looking at
    glm::vec3(upVector)    // Up vector (usually (0, 1, 0) for Y-up coordinate system)
);
```
This function constructs a view matrix as follows:
$$\begin{bmatrix}
s_x & s_y & s_z & -\mathbf{s} \cdot \mathbf{e} \\
u_x & u_y & u_z & -\mathbf{u} \cdot \mathbf{e} \\
-f_x & -f_y & -f_z & \mathbf{f} \cdot \mathbf{e} \\
0 & 0 & 0 & 1
\end{bmatrix}$$

Where:
- $ \mathbf{e} $ is the camera position.
- $ \mathbf{f} $ is the forward vector (normalized direction from the camera position to the target position).
- $ \mathbf{u} $ is the up vector (usually (0, 1, 0)).
- $ \mathbf{s} $ is the side vector, calculated as $ \mathbf{s} = \mathbf{f} \times \mathbf{u} $.

### Projection Matrix
The **projection matrix** transforms camera coordinates to normalized device coordinates (NDC). There are two main types of projection matrices: orthographic and perspective.
#### Perspective Projection Matrix
For perspective projection, we use the `glm::perspective` function:
```cpp
glm::mat4 projection = glm::perspective(
glm::radians(fov), // Field of view in radians
aspectRatio, // Aspect ratio (width/height)
nearPlane, // Near clipping plane
farPlane // Far clipping plane
);
```
The perspective projection matrix looks like this:
$$ P = \begin{bmatrix}
\frac{1}{\tan(\theta/2) \cdot a} & 0 & 0 & 0 \\
0 & \frac{1}{\tan(\theta/2)} & 0 & 0 \\
0 & 0 & \frac{-(f+n)}{f-n} & \frac{-2fn}{f-n} \\
0 & 0 & -1 & 0
\end{bmatrix} $$
Where:
- $ \theta $ is the field of view angle.
- $ a $ is the aspect ratio (width/height).
- $ n $ and $ f $ are the near and far clipping planes, respectively.
#### Orthographic Projection Matrix
For orthographic projection, we use the `glm::ortho` function:
```cpp
glm::mat4 projection = glm::ortho(
left, // Left clipping plane
right, // Right clipping plane
bottom, // Bottom clipping plane
top, // Top clipping plane
near, // Near clipping plane
far // Far clipping plane
);
```
The orthographic projection matrix looks like this:
$$ P = \begin{bmatrix}
\frac{2}{r-l} & 0 & 0 & \frac{-(r+l)}{r-l} \\
0 & \frac{2}{t-b} & 0 & \frac{-(t+b)}{t-b} \\
0 & 0 & \frac{-2}{f-n} & \frac{-(f+n)}{f-n} \\
0 & 0 & 0 & 1
\end{bmatrix} $$
Where:
- $ l $ is the left clipping plane.
- $ r $ is the right clipping plane.
- $ b $ is the bottom clipping plane.
- $ t $ is the top clipping plane.
- $ n $ and $ f $ are the near and far clipping planes, respectively.
### Using the Matrices in Shaders
Once you have the view and projection matrices, you need to pass them to your shaders and apply them to your vertex positions. In the vertex shader, you typically multiply the projection matrix by the view matrix, and then by the model matrix:
```glsl
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
gl_Position = projection * view * model * vec4(aPos, 1.0);
}
```
This transforms the vertex positions from model space to world space (using the model matrix), then to camera space (using the view matrix), and finally to NDC (using the projection matrix).
By understanding these matrices and their transformations, you can effectively control how your 3D scene is viewed and projected onto a 2D screen.