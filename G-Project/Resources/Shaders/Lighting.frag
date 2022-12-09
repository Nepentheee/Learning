#version 330 core

struct Material {
    float shininess;
    
    sampler2D diffuse;
    sampler2D specular;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


// Direction Light
vec3 CalcDirLight(Material material, DirLight light, vec3 normal, vec3 viewDir, vec2 textCoord)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    vec3 ambient = light.ambient * vec3(1,1,1); // vec3(texture(material.diffuse, textCoord));
    vec3 diffuse = light.diffuse * diff * vec3(1,1,1); //vec3(texture(material.diffuse, textCoord));
    vec3 specular = light.specular * spec * vec3(1,1,1); //vec3(texture(material.specular, textCoord));
    
    return (ambient + diffuse + specular);
}

// Point Light
vec3 CalcPointLight(Material material, PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 textCoord)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, normal), 0), material.shininess);

    // 衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    vec3 ambient = attenuation * light.ambient * vec3(texture(material.diffuse, textCoord));
    vec3 diffuse = attenuation * light.diffuse * diff * vec3(texture(material.diffuse, textCoord));
    vec3 specular = attenuation * light.specular * spec * vec3(texture(material.specular, textCoord));

    return (ambient + diffuse + specular);
}

// Spot Light
vec3 CalcSpotLight(Material material, SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 textCoord)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    if (theta > light.cutOff)
    {
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        float diff = max(dot(normal, lightDir), 0);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

        vec3 ambient = light.ambient * vec3(texture(material.diffuse, textCoord));
        vec3 diffuse = intensity * light.diffuse * diff * vec3(texture(material.diffuse, textCoord));
        vec3 specular = intensity * light.specular * spec * vec3(texture(material.specular, textCoord));

        return (ambient + diffuse + specular);
    }
    else
    {
        return vec3(light.ambient * vec3(texture(material.diffuse, textCoord)));
    }
}

#define NR_POINT_LIGHT 4

in vec3 v_normal;
in vec3 v_fragPos;
in vec2 v_Texcoord;

uniform vec3 u_viewPos;

uniform Material u_material;
uniform DirLight u_dirLight;
uniform SpotLight u_spotLight;
uniform PointLight u_pointLights[NR_POINT_LIGHT];

uniform sampler2D u_Texture;

layout(location = 0) out vec4 color;

void main()
{
    vec3 normal = normalize(v_normal);
    vec3 viewDir = normalize(u_viewPos - v_fragPos);

    vec3 result = CalcDirLight(u_material, u_dirLight, normal, viewDir, v_Texcoord);
//    for(int i = 0; i < NR_POINT_LIGHT; i++)
//        result += CalcPointLight(u_material, u_pointLights[i], normal, v_fragPos, viewDir, v_Texcoord);
//    
//    result += CalcSpotLight(u_material, u_spotLight, normal, v_fragPos, viewDir, v_Texcoord);

//    color = vec4(result, 1);
//    color = texture(u_Texture, v_Texcoord) * vec4(result, 1);
    color = vec4(1,0,0,1) * vec4(result, 1);
};