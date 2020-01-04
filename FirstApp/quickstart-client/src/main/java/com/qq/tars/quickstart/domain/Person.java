package com.qq.tars.quickstart.domain;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Transient;

import org.hibernate.annotations.Type;

@Entity 
@Table(name="t_person")
public class Person {
	private int id;
	private String name;
	private double money;

	public void setId(int id) {
		this.id = id;
	}

	public int getId(){
		return id;
	}

	public void setName(String name){
		this.name = name;
	}

	public String getName(){
		return name;
	}

	public void setMoney(double money){
		this.money = money;
	}

	public double getMoney(){
		return money;
	}
}
