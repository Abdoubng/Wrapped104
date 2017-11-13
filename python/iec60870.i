/* File : iec60870.i */
%module iec60870

%ignore T104Slave_createSecure;
%{
#include "iec60870_common.h"
#include "iec60870_slave.h"
#include "information_objects.h"
#include "server.hpp"

%}
%include "iec60870_common.h"
%include "iec60870_slave.h"


%include "information_objects.h"
/*%include "callbacks.h"*/
%include "server.hpp"

