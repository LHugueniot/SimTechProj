#ifndef CLOTHSIMLIB_GLOBAL_H
#define CLOTHSIMLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/fast_square_root.hpp"
#include <glm/gtx/transform.hpp>
#undef GLM_ENABLE_EXPERIMENTAL
#include <glm/geometric.hpp>

#include <vector>
#include <memory>
#if defined(CLOTHSIMLIB_LIBRARY)
#  define CLOTHSIMLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLOTHSIMLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CLOTHSIMLIB_GLOBAL_H
