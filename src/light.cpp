#include "light.h"

Light::Light(Vector4f pos, Vector3f i) : position(pos), intensity(i) {}

Vector3f lighting(Material material, Light light, Vector4f point, Vector4f eyev,
                  Vector4f normalv) {
  Vector3f ambient, diffuse, specular;
  Vector3f black{0, 0, 0};
  // combine the surface color with the light's color/intensity
  Vector3f effectiveColor = material.color.cwiseProduct(light.intensity);

  // find the direction to the light source
  Vector4f lightv = (light.position - point).normalized();

  // compute the ambient contribution
  ambient = effectiveColor * material.ambient;

  // lightDotNormal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface.
  float lightDotNormal = lightv.dot(normalv);
  if (0 > lightDotNormal) {
    diffuse = black;
    specular = black;
  } else {
    // compute the diffuse contribution
    diffuse = effectiveColor * material.diffuse * lightDotNormal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the eye vector. A negative number means the
    // light reflects away from the eye.
    Vector4f reflectv = reflect(-lightv, normalv);
    float reflectDotEye = reflectv.dot(eyev);

    if (0 >= reflectDotEye) {
      specular = black;
    } else {
      float factor = pow(reflectDotEye, material.shininess);
      specular = light.intensity * material.specular * factor;
    }
  }
  return ambient + diffuse + specular;
}
