#pragma once

#define GETTER(TYPE, VARNAME) TYPE get_##VARNAME##() const { return VARNAME; }
#define SETTER(TYPE, VARNAME) void set_##VARNAME##(TYPE value){ VARNAME = value; }

#define GETTERSETTER(TYPE, VARNAME) GETTER(TYPE, VARNAME); SETTER(TYPE, VARNAME)