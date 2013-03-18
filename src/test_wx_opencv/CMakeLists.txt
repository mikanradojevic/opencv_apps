set(TARGET test_wx_opencv)

set(WX_LIB_FILES
	wxbase28u.lib
	wxexpat.lib
	wxjpeg.lib
	wxmsw28u_core.lib
	wxpng.lib
	wxregexu.lib
	wxtiff.lib
	wxzlib.lib 
	winmm.lib
	comctl32.lib
	rpcrt4.lib
	mathplot.lib
	) 
	
set(WX_LIB_FILES_DBG
	wxbase28ud.lib
	wxexpatd.lib
	wxjpegd.lib
	wxmsw28ud_core.lib
	wxpngd.lib
	wxregexud.lib
	wxtiffd.lib 
	wxzlibd.lib 
	winmm.lib
	comctl32.lib
	rpcrt4.lib
	mathplotd.lib
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
	prerequisites.h
	app.cpp
	app.h
	image_frame.cpp
	image_frame.h
	graph_frame.cpp
	graph_frame.h
	overview_frame.cpp
	overview_frame.h
	ocv_canvas.cpp
	ocv_canvas.h
	graph_canvas.cpp
	graph_canvas.h
	ocv_cam_canvas.cpp
	ocv_cam_canvas.h
	gui_classes.cpp
	gui_classes.h 
	)
	
set(OTHER_SRC_FILES
	graph.cpp
	graph.h
	image.cpp
	image.h
	utils.cpp
	utils.h
	video_capture.cpp
	video_capture.h
	)
	
if(WIN32)
  set(RES_FILES minimal.rc)
endif(WIN32) 

source_group("src" FILES ${OTHER_SRC_FILES}) 
source_group("wx_src" FILES ${UI_FILES})
source_group("res" FILES ${RES_FILES})

add_definitions(-DUNICODE)

set(SRC_FILES 
	${OTHER_SRC_FILES}
	${UI_FILES} 
	${RES_FILES}
	)
	
add_executable(${TARGET} WIN32 ${SRC_FILES})
set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX "_debug")

target_link_libraries(${TARGET} debug "${WX_LIB_FILES_DBG}")
target_link_libraries(${TARGET} optimized "${WX_LIB_FILES}")
target_link_libraries(${TARGET} debug "${OCV_LIB_FILES_DBG}")
target_link_libraries(${TARGET} optimized "${OCV_LIB_FILES}")

# Installation
install(TARGETS ${TARGET} RUNTIME DESTINATION bin/${TARGET})
install(DIRECTORY ${DEP_DLL_DIR} DESTINATION bin/${TARGET}) 