// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from voyager_msgs:srv/GetTransform.idl
// generated code does not contain a copyright notice

#ifndef VOYAGER_MSGS__SRV__DETAIL__GET_TRANSFORM__STRUCT_H_
#define VOYAGER_MSGS__SRV__DETAIL__GET_TRANSFORM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'frame_id'
// Member 'child_frame_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetTransform in the package voyager_msgs.
typedef struct voyager_msgs__srv__GetTransform_Request
{
  rosidl_runtime_c__String frame_id;
  rosidl_runtime_c__String child_frame_id;
} voyager_msgs__srv__GetTransform_Request;

// Struct for a sequence of voyager_msgs__srv__GetTransform_Request.
typedef struct voyager_msgs__srv__GetTransform_Request__Sequence
{
  voyager_msgs__srv__GetTransform_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} voyager_msgs__srv__GetTransform_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'transform'
#include "geometry_msgs/msg/detail/transform_stamped__struct.h"

/// Struct defined in srv/GetTransform in the package voyager_msgs.
typedef struct voyager_msgs__srv__GetTransform_Response
{
  geometry_msgs__msg__TransformStamped transform;
  bool success;
} voyager_msgs__srv__GetTransform_Response;

// Struct for a sequence of voyager_msgs__srv__GetTransform_Response.
typedef struct voyager_msgs__srv__GetTransform_Response__Sequence
{
  voyager_msgs__srv__GetTransform_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} voyager_msgs__srv__GetTransform_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOYAGER_MSGS__SRV__DETAIL__GET_TRANSFORM__STRUCT_H_
