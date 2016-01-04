
#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 projection_matrix, view_matrix;
uniform vec3 position, rotation, camera_position, camera_rotation;//, cameraTranslate;


out vec4 color;

void main()
{

	color = in_color;
	mat4 translation, camera_rotation_y, camera_rotation_x, camera_rotation_z, camera_translation, rotate_y, camera_frotation, camera_rtranslation;

	rotate_y = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0,
					0.0, 1.0, 0.0, 0.0,
					sin(rotation.y), 0.0, cos(rotation.y), 0.0,
					0.0, 0.0, 0.0, 1.0);
	
	camera_rotation_x = mat4(1.0, 0.0, 0.0, 0.0,
					0.0, cos(camera_rotation.x), sin(camera_rotation.x), 0.0,
					0.0, -sin(camera_rotation.x), cos(camera_rotation.x), 0.0,
					0.0, 0.0, 0.0, 1.0);

	camera_rotation_y = mat4(cos(camera_rotation.y), 0.0, -sin(camera_rotation.y), 0.0,
					0.0, 1.0, 0.0, 0.0,
					sin(camera_rotation.y), 0.0, cos(camera_rotation.y), 0.0,
					0.0, 0.0, 0.0, 1.0);

	camera_rotation_z = mat4(cos(camera_rotation.z), -sin(camera_rotation.z), 0.0, 0.0,
					sin(camera_rotation.z), cos(camera_rotation.z), 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0);

	translation = mat4(1.0, 0.0, 0.0, 0.0,
					   0.0, 1.0, 0.0, 0.0,
					   0.0, 0.0, 1.0, 0.0,
					   position.x, position.y, position.z, 1.0);

	camera_translation = mat4(1.0, 0.0, 0.0, 0.0,
					   0.0, 1.0, 0.0, 0.0,
					   0.0, 0.0, 1.0, 0.0,
					   camera_position.x, camera_position.y, camera_position.z, 1.0);
	
	camera_rtranslation = mat4(1.0, 0.0, 0.0, 0.0,
					   0.0, 1.0, 0.0, 0.0,
					   0.0, 0.0, 1.0, 0.0,
					   -camera_position.x, -camera_position.y, -camera_position.z, 1.0);
	camera_frotation =  camera_rotation_x * camera_rotation_y * camera_rotation_z;

	

	gl_Position = projection_matrix * camera_translation * camera_frotation * view_matrix * translation * rotate_y * vec4(in_position, 1);
	
}