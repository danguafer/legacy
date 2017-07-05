#include "ComputeProgram.h"
#include "third-party/glLoader/glLoader.h"

using namespace Silexars;
using namespace Graphics::API;
using namespace Shaders;
using namespace Samplers;

ComputeProgram::ComputeProgram(ComputeShader *cs) {
    this->cs = cs;
    glAttachShader((GLuint) id, (GLuint) cs->id);
    link();
}

ComputeShader* ComputeProgram::getComputeShader() const { return cs; }

void ComputeProgram::compute(uint32 w, uint32 h, uint32 d) {
    use();
    for (uint32 i = 0; i < samplers.nbindings; i++) {
        LocationBinding lbinding = samplers.bindings[i];
        Sampler* sampler = (Sampler*) lbinding.object;
        sampler->use(i);
        getLocalUniformBuffer()->uniform(lbinding.location, (int32) i);
        sampler->bindImage(i, lbinding.permission);
    }

    glDispatchCompute(w, h, d);
}

void ComputeProgram::sampler(int32 uniform, Sampler *sampler, uint8 permission) { samplers.set(uniform, sampler, permission); }
void ComputeProgram::sampler(const char *s, Sampler *sampl, uint8 permission) { sampler(getLocalUniformBuffer()->getUniformLocation(s), sampl, permission); }
