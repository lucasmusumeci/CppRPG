/*
 * Capacite.cpp
 *
 *  Created on: 12 Dec 2025
 *      Author: lucas
 */

#include "move.hpp"


float getTypeBonus(Type attack_type, Type defense_type1, Type defense_type2)
{
	return type_bonus[attack_type][defense_type1] * type_bonus[attack_type][defense_type2];
}

/*
 * Constructors
 */
Move::Move()
{
	this->id = 0;
	this->name = "";
	this->base_power = 0;
	this->precision = 0.0f;
	this->category = NULL_CATEGORY;
	this->type = NULL_TYPE;
	this->buff = 0;
	this->stat = NULL_STAT;
	this->buff_target = NULL_TARGET;
}

Move::Move(sqlite3* db, int id)
{
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT Id,Name,BasePower,Precision,Id_Category,Id_type,Stat_Buff,Id_Stat,Buff_Target FROM move WHERE Id = ?;";
    // Prepare the statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare SQL statement");
    }
    // Bind parameter (id)
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
    	this->id = sqlite3_column_int(stmt, 0);
    	this->name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    	this->base_power = sqlite3_column_int(stmt, 2);
    	this->precision = sqlite3_column_int(stmt, 3) * 0.01f;
    	this->category = static_cast<Category>(sqlite3_column_int(stmt, 4));
    	this->type = static_cast<Type>(sqlite3_column_int(stmt, 5));
    	this->buff = sqlite3_column_int(stmt, 6);
    	this->stat = static_cast<Stat>(sqlite3_column_int(stmt, 7));
    	this->buff_target = static_cast<Buff_Target>(sqlite3_column_int(stmt, 8));
    }
    else
    {
    	sqlite3_finalize(stmt);
    	throw std::runtime_error("No move with this id in database");
    }

    sqlite3_finalize(stmt);
}

Move::Move(sqlite3* db, std::string &name)
{
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT Id,Name,BasePower,Precision,Id_Category,Id_type,Stat_Buff,Id_Stat,Buff_Target FROM move WHERE Name = ?;";
    // Prepare the statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare SQL statement");
    }
    // Bind parameter (const char*) => need to cast
    sqlite3_bind_text(stmt, 1, name.c_str(),-1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
    	this->id = sqlite3_column_int(stmt, 0);
    	this->name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    	this->base_power = sqlite3_column_int(stmt, 2);
    	this->precision = sqlite3_column_int(stmt, 3) * 0.01f;
    	this->category = static_cast<Category>(sqlite3_column_int(stmt, 4));
    	this->type = static_cast<Type>(sqlite3_column_int(stmt, 5));
    	this->buff = sqlite3_column_int(stmt, 6);
    	this->stat = static_cast<Stat>(sqlite3_column_int(stmt, 7));
    	this->buff_target = static_cast<Buff_Target>(sqlite3_column_int(stmt, 8));
    }
    else
    {
    	sqlite3_finalize(stmt);
    	throw std::runtime_error("No move with this name in database");
    }

    sqlite3_finalize(stmt);
}

/*
 * Destructor
 */
Move::~Move()
{
	//std::cout << "Move " << name << " was destroyed" << std::endl;
}

/*
 * Getters
 */
int Move::getId()
{
    return id;
}
std::string& Move::getName()
{
    return name;
}
int Move::getBasePower()
{
    return base_power;
}
float Move::getPrecision()
{
    return precision;
}
Category Move::getCategory()
{
    return category;
}
Type Move::getType()
{
    return type;
}
int Move::getBuff()
{
    return buff;
}
Stat Move::getStat()
{
    return stat;
}
Buff_Target Move::getBuffTarget()
{
    return buff_target;
}

/*
 * Methods
 */
bool Move::isEmpty()
{
	if(id) return 0;
	return 1;
}



