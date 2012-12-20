set(TARGET test_opencv)

set(WX_LIB_FILES
	) 
	
set(OCV_LIB_FILES
	opencv_core243.lib
	opencv_highgui243.lib
	opencv_video243.lib
	opencv_ml243.lib
	opencv_legacy243.lib
	opencv_imgproc243.lib
	) 
	
set(OCV_LIB_FILES_DBG
	opencv_core243d.lib
	opencv_highgui243d.lib
	opencv_video243d.lib
	opencv_ml243d.lib
	opencv_legacy243d.lib
	opencv_imgproc243d.lib
	) 

set(UI_FILES
	opencv_hello.cpp
	)
	
if(WIN32)
  set(RES_FILES minimal.rc)
endif(WIN32) 

source_group("source" FILES ${UI_FILES})
source_group("res" FILES ${RES_FILES})

add_definitions(-DUNICODE)

set(SRC_FILES 
	${UI_FILES} 
	${RES_FILES}
	)
	
add_executable(${TARGET} ${SRC_FILES})
set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX "_debug")

target_link_libraries(${TARGET} ${WX_LIB_FILES})
target_link_libraries(${TARGET} debug "${OCV_LIB_FILES_DBG}")
target_link_libraries(${TARGET} optimized "${OCV_LIB_FILES}")

# Installation
install(TARGETS ${TARGET} RUNTIME DESTINATION bin/${TARGET})
install(DIRECTORY ${DEP_DLL_DIR} ${DEP_DLL_DIR} DESTINATION bin/${TARGET}) 