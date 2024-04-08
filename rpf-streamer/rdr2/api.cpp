#include "script.h"

Player getPlayer() {
	return PLAYER::PLAYER_ID();
}

Ped getPlayerPed() {
	return PLAYER::PLAYER_PED_ID();
}

Ped getPlayerHorse() {
	return PLAYER::_GET_ACTIVE_HORSE_FOR_PLAYER(getPlayer());
}

Vector3 getEntityCoords(Entity entity) {
	return ENTITY::GET_ENTITY_COORDS(entity, true, 0);
}

Vector3 getPlayerCoords() {
	return getEntityCoords(getPlayerPed());
}

