package com.pxhua.video.common;

//import com.qq.tars.protocol.annotation.*;
//import com.qq.tars.protocol.tars.annotation.*;
//import com.qq.tars.common.support.Holder;

//import com.pxhua.video.proto.httpproto.HttpCGIServant;
//import com.pxhua.video.proto.httpproto.st_cgi_req;
//import com.pxhua.video.proto.httpproto.st_cgi_rsp;
//import com.pxhua.video.proto.account.AccessServant;
//import com.pxhua.video.proto.account.st_login_verify_req;
//import com.pxhua.video.proto.account.st_login_verify_rsp;

import redis.clients.jedis.Jedis;

public class RedisLock {

	private String _host = null;
	private int _port;
	private int _timeout = 60;
	private int _is_connected = 0;
	private Jedis _jedis = null;

	private String _key = null;
	private boolean _is_locked = false;
	private long _cur_time = 0;

	private final static Logger _flow_log = Logger.getLogger("flow", LogType.LOCAL);

	public enum LockError{
		E_REDIS_ERROR		= -1,
		E_CONNECT_FIALED	= -2,
		E_LOCK_FAILED		= -3,
		E_HAS_LOCKED		= -4,
	} 

	public RedisLock(String host, int port)
	{
		_host = host;
		_port = port;
		_timeout = 60;
		redisConnect();
	}

	public RedisLock(String host, int port, int timeout)
	{
		_host = host;
		_port = port;
		_timeout = timeout;
		redisConnect();
	}

	private int redisConnect()
	{
		try{
			_jedis = new Jedis(host, port); // how to check connection failed
			_is_connected = 1;
		}
		catch(JedisConnectionException jce)
		{
			_flow_log.error("jedis connect failed, msg: " + jce.getMessage() + ", cause: " << jce.getCause());
			return E_CONNECT_FIALED;
		}
		catch (JedisException e)
		{
			_flow_log.error("jedis exception, msg: " + e.getMessage() + ", cause: " << e.getCause());
			return E_CONNECT_FIALED;
		}
		return 0;
	}

	public void finalize()
	{
		if(_jedis != null)
		{
			if(_is_locked && _key != null)
			{
				unlock();
			}
			_jedis.quit();
		}
	}

	public int lock(String key)
	{
		int ret = 0;
		if(_is_connected != 0)
		{
			ret = redisConnect();
			if(ret != 0)
			{
				return E_CONNECT_FIALED;
			}
		}

		_key = key;
		_cur_time = System.currentTimeMillis() / 1000;
		try{
			Long result = _jedis.setnx(key, String.valueOf(_cur_time));
			if(1 == result)
			{
				_flow_log.debug("lock success, key: " + key);
				_is_locked = true;
			}
			else if(0 != result)
			{
				_flow_log.error("lock failed, key: " + key + ", result: " + result);
				ret = E_LOCK_FAILED;
			}
			else
			{
				ret = checkDeadLock(key);
				if(0 == ret)
				{
					//TODO: lock again
				}
			}
		}
		cacth(JedisException e)
		{
			ret = E_REDIS_ERROR;
			_flow_log.error("redis lock failed, key: " + key + ", exception: " + e.getMessage());
		}

		return ret;
	}

	public int unlock()
	{
		// TODO
		if(_is_locked)
		{

		}
	}

	private int checkDeadLock(String key)
	{
		int ret = 0;
		try{

			String sResult = _jedis.get(key);
			long pre_time = Long.parseLong(sResult);
	    	if(_cur_time - pre_time <= long(_timeout))
			{
				_flow_log.debug("no dead redis lock, key: " + key);
				return 0;
			}

			// lock has timeout and delete
			sResult = _jedis.getset(key, String.valueOf(_cur_time));
			long pre_time2 = Long.parseLong(sResult);
			if(pre_time != pre_time2)
			{
				return E_REDIS_ERROR; // maybe locked by others
			}

			_flow_log.debug("need release dead redis lock, key: " + key);

			unlock();
		}
		cacth(JedisException e)
		{
			ret = E_REDIS_ERROR;
			_flow_log.error("check dead redis lock failed, key: " + key + ", exception: " + e.getMessage());
		}

		return ret;
	}
}


