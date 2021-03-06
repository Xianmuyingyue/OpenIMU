SET(srcs
    ${srcs}    
	${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmDetailedView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationMenuBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyTreeWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RangeSlider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyListWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmTab.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RecordViewWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ResultsTabWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HomeWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StepCounterResults.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActivityTrackerResults.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericAlgoResults.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MRichTextEditor/mrichtextedit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MRichTextEditor/mtextedit.cpp

    PARENT_SCOPE
)

SET(headers
    ${headers}
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmDetailedView.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationMenuBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MyTreeWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RangeSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MyListWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmTab.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ResultsTabWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HomeWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RecordViewWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StepCounterResults.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ActivityTrackerResults.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericAlgoResults.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MRichTextEditor/mrichtextedit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MRichTextEditor/mtextedit.h
    PARENT_SCOPE
)

SET(uis
    ${uis}
    ${CMAKE_CURRENT_SOURCE_DIR}/MRichTextEditor/mrichtextedit.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/recordviewwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/stepcounterresults.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/homewidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/activitytrackerresults.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/genericalgoresults.ui
    PARENT_SCOPE
)

add_custom_target(qml_files SOURCES ../rangeSlider.qml)
