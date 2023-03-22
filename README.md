# OpenGLIntro

## A Collection of Projects as I try to learn OpenGL

### *OpenGLIntro*

Based on TheCherno's intro to OpenGL series, largely be just following along. In the long run I wouldn't say I learnt a lot about how to do things myself, but regardless it got me started and helped me work on my C++ a bit more.


### *Segmented Display Simulator*

Trying to put what I learnt into practice. A simulator for a Seven Segmented Display (may be more than 7 in the future).

### *Learn Open GL*

Based on the Learn Open GL book/guides. A bit more of a freeform way for me to work along and figure out how openGL works. Arguably the meat of this entire repository since I'm not really following a guide and really just trying to make things on my own. Listed below are a couple "subprojects," just me trying to see if I can render whatever idea I had in my head or help practice some openGL tool or general computer graphics concept.

#### Subprojects:

#### ***Bouncing Logo***

Tried to recreate those old bouncing DVD Logo screens. This was prior to really knowing how to work with MVPs at all, so all the buffer coordinates are mapped onto Clip Space from the get go. Bouncing is just done by checking against the screen boundaries (in clip space, so -1 and 1) and multiplying a velocity vector by { -1, 0 } or { 0, -1 } depending on whether the boundary was crossed on the x or y axis.

`
int w, h;
velocity.x = (float) copysign (1, velocity.x) * ((float) w / ( w * 144));
velocity.y = (float) copysign (1, velocity.y) * ((float) h / ( h * 168));

offsetV = addVector(offsetV, velocity);
if (offsetV.x + 0.25f >= 1.0f || offsetV.x - 0.25f <= -1.0f) velocity.x *= -1;
if (offsetV.y + 0.25f >= 1.0f || offsetV.y - 0.25f <= -1.0f) velocity.y *= -1;
`


#### ***Draw Droplet***

This one mostly involves messing with the Fragment Shader & Vertex Shader as well as uniforms and textures. There's also a bit of model matrix transformation used in order to rotate along the y-axis

```
glm::mat4 trans = glm::mat4(1.0f);

...

{
    myShader.useShader();
    trans = glm::rotate(trans, (float) glm::radians (1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate on y axis
    myShader.setUniformMatrix4fv("transform", 1, trans);

    ...

}
```

##### ***Draw Array Prisms***

###### Functions made for this:

- `get_max_and_min (int *mat, unsigned int MAT_SIZE);`
- `normalize_int (int val, int min, int max);`
- `drawPrism (glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float height);`
- `drawMatrixPrisms (int *mat, unsigned int MAT_SIZE);`

Takes in an array and draws thems as prisms in the from of a strip. The primary work is done in `drawMatrixPrisms (int *mat, unsigned int MAT_SIZE)` and `drawPrism(glm::vec3 p1, ..., glm::vec3 p4, float height)`.
Height is normalized based on maximum and minimum array values, and implemented in the function `float normalize_int (int val, int min, int max)`. The length of the rendered chain (int terms of numbers of prisms) is always `MAT_SIZE - 1`.

![Draw Array Prisms GIF](https://github.com/KaytchJam/OpenGLIntro/blob/master/openGL_screenshots/drawMatrixPlane_EX1.gif?raw=true)

In working on this I mostly learnt about basic Model View Projection matrix manipulations and rendering in 3D spaces. Model matrix for scaling and translating the prisms properly, and the View matrix so that I could rotate around the entire prism chain and not have to apply a transformation on the prisms individually. One thing I could potentially do is coalesce all the vertex array objects created into one singular vertex array, which would probably involve merging the Vertex Buffers & Index Buffers of all prisms in the chain. 


