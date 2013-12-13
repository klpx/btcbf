// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <time.h>

#include <tchar.h>

#include <omp.h>

#define HAVE_WORKING_BOOST_SLEEP

#include "bitcoin/allocators.h"
#include "bitcoin/base58.h"
#include "bitcoin/clientversion.h"
#include "bitcoin/hash.h"
#include "bitcoin/key.h"
#include "bitcoin/serialize.h"
#include "bitcoin/uint256.h"
#include "bitcoin/version.h"

// TODO: reference additional headers your program requires here
