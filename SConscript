# -*- python -*-
# $Header$
# Authors: Bryson Lee <blee@slac.stanford.edu>
# Version: eventFile-09-00-00
Import('baseEnv')
Import('listFiles')
Import('packages')
libEnv = baseEnv.Clone()

if baseEnv['PLATFORM'] != "win32":
    libEnv.AppendUnique(CPPDEFINES = ['_FILE_OFFSET_BITS=64'])
else:
    libEnv.AppendUnique(CPPDEFINES = ['__i386'])
    libEnv.AppendUnique(CCFLAGS = '/Zp4')
libEnv.AppendUnique(CPPDEFINES = ['HAVE_FACILITIES'])
progEnv = libEnv.Clone()
swigEnv = libEnv.Clone()

libEnv.Tool('eventFileLib', depsOnly = 1)
eventFile = libEnv.SharedLibrary('eventFile', ['src/EBF_Data.cxx', 'src/LSE_Context.cxx', 'src/LSE_GemTime.cxx',
                                               'src/LSE_Info.cxx', 'src/LSEHeader.cxx', 'src/LSEReader.cxx',
                                               'src/LSEWriter.cxx', 'src/LSE_Keys.cxx', 'src/LPA_Handler.cxx'])
swigEnv.Tool('eventFileLib')
lib_pyeventFile = swigEnv.SharedLibrary( 'lib_py_eventFile', ['src/py_eventFile.i'] )

progEnv.Tool('eventFileLib')
writeMerge = progEnv.Program('writeMerge.exe', 'src/writeMerge.cxx')
test_LSEReader = progEnv.Program('test_LSEReader.exe', 'src/test/test_LSEReader.cxx')

progEnv.Tool('registerObjects', package = 'eventFile',
             libraries = [eventFile, lib_pyeventFile],
             binaries = [writeMerge],
             testApps = [test_LSEReader],
             includes = listFiles(['eventFile/*.h']),
             python   = ['src/py_eventFile.py'])

                                                                
