package com.qq.tars.quickstart.domain;

import com.qq.tars.quickstart.domain.Person;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;
import org.junit.Test;

import java.util.Properties;

public class HibernateTest {
    public static void test() {
        //1）加载Hibernate的核心的配置文件（使用什么数据库？什么方言？等）
        Configuration configure = new Configuration().configure();
        //2）创建一个SessionFactory对象：类似于JDBC中的连接池，维护连接池或者是缓存
        SessionFactory factory = configure.buildSessionFactory();
        //3）有SessionFactory来创建一个Session的对象，类似于JDBC中的Connection的对象
        Session session = factory.openSession();
        //4）手动的开启事务
        //Transaction transaction = session.beginTransaction();
        //5）编写代码
        Person person = new Person();
        //person.setId(13);
        person.setMoney(1000d);
        person.setName("sunmoumou123456");
        session.save(person);
        //6）事务提交
        //transaction.commit();
        //7）资源释放
        session.close();
    }
}


