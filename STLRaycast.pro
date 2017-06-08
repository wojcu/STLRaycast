TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -=

LIBS += -pthread

SOURCES += main.cpp \
    graphics/camera.cpp \
    graphics/color.cpp \
    graphics/image.cpp \
    graphics/material.cpp \
    graphics/point_light.cpp \
    graphics/render_context.cpp \
    graphics/scene.cpp \
    math/mat4.cpp \
    math/vec2.cpp \
    math/vec3.cpp \
    math/vec4.cpp \
    physics/collider.cpp \
    physics/collision_context.cpp \
    physics/plane_collider.cpp \
    physics/ray.cpp

HEADERS += \
    graphics/camera.hpp \
    graphics/color.hpp \
    graphics/image.hpp \
    graphics/material.hpp \
    graphics/point_light.hpp \
    graphics/render_context.hpp \
    graphics/scene.hpp \
    math/mat4.hpp \
    math/vec2.hpp \
    math/vec3.hpp \
    math/vec4.hpp \
    physics/collider.hpp \
    physics/collision_context.hpp \
    physics/plane_collider.hpp \
    physics/ray.hpp
