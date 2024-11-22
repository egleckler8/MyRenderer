After school ended in May 2024, emboldened by my fresh course experience in C++, linear algebra, 
and multi-variable calculus, I decided to explore my long-standing interest of procedural generation.
Logically, the first step step was to build my own rendering engine so that I could create 3D procedural 
without any limitation imposed by an external tool, e.g. Unity... So, I started working out of the
[LearnOpenGL](https://learnopengl.com/) book.

Unfortunately, it was time to move out and begin my summer internship before I got to the 
procedural generation part. Since then, I have been quite busy and have not had the proper
energy to devote to this project, very sadly. Happily, I learned quite a bit along the way
about computer graphics, developing in C++, and got to practice a lot of fun software design.

So, this repo marks the state of the project as I left it at the end of in May 2024. 
If you look at the code, you'll find a deferred renderer with the Blinn-Phong lighting model.
Right at the end of may, I was working on implementing a skybox--but this seemed somewhat
ungainly to me in my deferred renderer. So, I ambitiously decided that I would convert the
renderer to a hybrid model and implement Physically Based Rendering in the process. As above,
I never actually got to that part--this is what is in the repo right now:

 - Deferred rendering engine build with the OpenGL graphics API in C++
 - Skeleton of software system for a future procedural game
 - Wavefront .obj model loader from json using assimp

