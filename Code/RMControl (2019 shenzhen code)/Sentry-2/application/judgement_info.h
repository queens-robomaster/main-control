/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file judgement_info.h
 *  @version 1.0
 *  @date June 2017
 *
 *  @brief the information from judgement system
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 */

#ifndef __JUDGEMENT_INFO_H__
#define __JUDGEMENT_INFO_H__

#include "stm32f4xx_hal.h"

#define JUDGE_FIFO_BUFLEN 500

/** 
  * @brief  judgement data command id
  */
typedef enum
{
  Competition_status_ID       = 0x0001,
	Competition_result_ID			= 0x0002,
	Competition_robots_servival_ID = 0x0003,
	Battlefield_event_ID = 0x0101,
	Battlefield_Projectile_Supplier_ID = 0x0102,
	Request_projectile_supply_ID = 0x0103,
	Robot_status_ID = 0x0201,
	Power_heat_ID = 0x0202,
	Robot_position_ID = 0x0203,
	Robot_gain_ID = 0x0204,
	Aerial_energy_ID = 0x0205,
	Damage_status_ID = 0x0206,
	Real_time_shooting_ID = 0x0207,
	Interaction_data_ID = 0x0301
} judge_data_id_e;


/** 
  * @brief  game information structures definition(0x0001)
  */
typedef __packed struct
{
	uint8_t game_type: 4;
	uint8_t game_process: 4;
	uint16_t stage_remain_time;
} ext_game_state_t;

/** 
  * @brief  Competition result data(0x0002)
  */
typedef __packed struct
{
  uint8_t winter;
} ext_game_result_t;

/** 
  * @brief  Robot survival data(0x0003)
  */
typedef __packed struct
{
  uint16_t robot_legion;
} ext_game_robot_survivors_t;

/** 
  * @brief  Battlefield event data (0x0101)
  */
typedef __packed struct
{
  uint32_t event_type;
} ext_event_data_t;

/** 
  * @brief  Projectile Supplier Zone(0x0102)
  */
typedef __packed struct
{
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
} ext_supply_projectile_action_t;

/** 
  * @brief  Request Projectile Supplier(0x0103)
  */
typedef __packed struct
{
  uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_num;
} ext_supply_projectile_booking_t;

/** 
  * @brief  Match robot status (0x0201)
  */
typedef __packed struct
{
  uint8_t robot_id;
	uint8_t robot_level;
	uint16_t remain_HP;
	uint16_t max_HP;
	uint16_t shooter_heat0_cooling_rate;
	uint16_t shooter_heat0_cooling_limit;
	uint16_t shooter_heat1_cooling_rate;
	uint16_t shooter_heat1_cooling_limit;
	uint8_t mains_power_gimbal_output: 1;
	uint8_t mains_power_chassis_output: 1;
	uint8_t mains_power_shooter_output: 1;
} ext_game_robot_state_t;

/** 
  * @brief  Real-time power and barrel heat(0x0202)
  */
typedef __packed struct
{
	uint16_t chassis_volt;
	uint16_t chassis_current;
	float chassis_power;
	uint16_t chassis_power_buffer;
	uint16_t shooter_heat0;
	uint16_t shooter_heat1;
} ext_power_heat_data_t;

/** 
  * @brief  Robot Position (0x0203)
  */
typedef __packed struct
{
	float x; 
	float y;
	float z;
	float yaw;
} ext_game_robot_pos_t;

/** 
  * @brief  Robot gain (0x0204)
  */
typedef __packed struct
{
	uint8_t power_rune_buff;
} ext_buff_musk_t;

/** 
  * @brief  Aerial energy status (0x0205)
  */
typedef __packed struct
{
	uint8_t energy_point;
	uint8_t attack_time;
} aerial_robot_energy_t;

/** 
  * @brief  Damage status (0x0206)
  */
typedef __packed struct
{
	uint8_t armor_id: 4;
	uint8_t hurt_type: 4;
} ext_robot_hurt_t;

/** 
  * @brief  Real-time shooting data(0x0207)
  */
typedef __packed struct
{
	uint8_t bullet_type;
	uint8_t bullet_freq;
	float bullet_speed;
} ext_shoot_data_t;

/** 
  * @brief  interactive data receiving information (0x0301)
  */
typedef __packed struct
{
	uint16_t data_cmd_id;
	uint16_t send_ID;
	uint16_t receiver_ID;
} ext_student_interactive_header_data_t;

/** 
  * @brief  interactive data -client (0xD180)
  */
typedef __packed struct
{
float data1;
float data2;
float data3;
uint8_t masks;
}client_custom_data_t;

typedef __packed struct{
uint8_t data[113];
}robot_interactive_data_t;

/** 
  * @brief  the data structure receive from judgement
  */
typedef struct
{
  ext_game_state_t game_status;
	ext_game_result_t game_result;
	ext_game_robot_survivors_t game_robot_survivors;
	ext_event_data_t event_data;
	ext_supply_projectile_action_t supply_projectile_action;
	ext_supply_projectile_booking_t supply_projectile_booking;
	ext_game_robot_state_t robot_state;
	ext_power_heat_data_t power_heat;
	ext_game_robot_pos_t game_robot_pos;
	ext_buff_musk_t buff_musk;
	aerial_robot_energy_t aerial_robot_energy;
	ext_robot_hurt_t robot_hurt_t;
	ext_shoot_data_t shoot_data;
	ext_student_interactive_header_data_t student_interactive_header;
	client_custom_data_t client_custom_data;
	robot_interactive_data_t robot_interactive_data;
} receive_judge_t;

/* data send (forward) */
/* data receive */
extern receive_judge_t judge_rece_mesg;

void  judgement_data_handler(uint8_t *p_frame);

#endif
