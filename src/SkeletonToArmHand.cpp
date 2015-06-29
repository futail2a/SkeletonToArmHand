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
    m_handOut("hand", m_hand)

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
  addOutPort("hand", m_handOut);
  
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
		//m_skeleton.SkeletonData[0].eSkeletonPositionTrackingState[0];
		Vector4 hand_r;
		hand_r = m_skeleton.SkeletonData[0].skeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
		m_hand.data.length(4);
		m_hand.data[0] = hand_r.v[0];
		m_hand.data[1] = hand_r.v[1];
		m_hand.data[1] = hand_r.v[2];
		m_hand.data[1] = hand_r.v[3];

		m_handOut.write();

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


