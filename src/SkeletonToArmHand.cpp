// -*- C++ -*-
/*!
 * @file  SkeletonToArmHand.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "SkeletonToArmHand.h"

// Module specification
// <rtc-template block="module_spec">
static const char* skeletontoarmhand_spec[] =
  {
    "implementation_id", "SkeletonToArmHand",
    "type_name",         "SkeletonToArmHand",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Asato Tao",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SkeletonToArmHand::SkeletonToArmHand(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_skeletonIn("skeleton", m_skeleton),
    m_hand_rOut("hand_r", m_hand_r),
    m_hand_lOut("hand_l", m_hand_l)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SkeletonToArmHand::~SkeletonToArmHand()
{
}



RTC::ReturnCode_t SkeletonToArmHand::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("skeleton", m_skeletonIn);
  
  // Set OutPort buffer
  addOutPort("hand_r", m_hand_rOut);
  addOutPort("hand_l", m_hand_lOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SkeletonToArmHand::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SkeletonToArmHand::onExecute(RTC::UniqueId ec_id)
{
	if (m_skeletonIn.isNew()){
		m_skeletonIn.read();

		//who was tracked
		for (int i = 0; i < 6; i++){
			if (m_skeleton.SkeletonData[i].trackingState == NUI_SKELETON_TRACKED){

				if (m_skeleton.SkeletonData[i].eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SPINE] == NUI_SKELETON_POSITION_TRACKED){
					m_spine.data.position.x = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_SPINE].v[0];
					m_spine.data.position.y = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_SPINE].v[1];
					m_spine.data.position.z = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_SPINE].v[2];
				}

				//If a right hand was tracked
				if (m_skeleton.SkeletonData[i].eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_RIGHT] == NUI_SKELETON_POSITION_TRACKED){
					m_hand_r.data.position.x = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].v[0] - m_spine.data.position.x;
					m_hand_r.data.position.y = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].v[1] - m_spine.data.position.y;
					m_hand_r.data.position.z = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].v[2] - m_spine.data.position.z;
					//m_hand_r.data[3] = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].v[3];
					m_hand_rOut.write();
				}

				//If a left hand was tracked
				if (m_skeleton.SkeletonData[i].eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT] == NUI_SKELETON_POSITION_TRACKED){
					m_hand_l.data.position.x = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].v[0] - m_spine.data.position.x;
					m_hand_l.data.position.y = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].v[1] - m_spine.data.position.y;
					m_hand_l.data.position.z = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].v[2] - m_spine.data.position.z;
					//m_hand_l.data[3] = m_skeleton.SkeletonData[i].skeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].v[3];
					m_hand_lOut.write();
				}
				break;
			}
			/*else{
				m_hand_r.data[0] = 0;
				m_hand_r.data[1] = 0;
				m_hand_r.data[2] = 0;
				m_hand_r.data[3] = 0;
				m_hand_rOut.write();

			}*/
		}
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SkeletonToArmHand::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SkeletonToArmHand::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SkeletonToArmHandInit(RTC::Manager* manager)
  {
    coil::Properties profile(skeletontoarmhand_spec);
    manager->registerFactory(profile,
                             RTC::Create<SkeletonToArmHand>,
                             RTC::Delete<SkeletonToArmHand>);
  }
  
};


