// **********************************************************************
// This file was generated by a TARS parser!
// TARS version 1.0.1.
// **********************************************************************

package com.pxhua.video.proto.account;

import com.qq.tars.protocol.util.*;
import com.qq.tars.protocol.annotation.*;
import com.qq.tars.protocol.tars.*;
import com.qq.tars.protocol.tars.annotation.*;

@TarsStruct
public class st_login_verify_req {

	@TarsStructProperty(order = 0, isRequire = true)
	public int token_mode = 0;
	@TarsStructProperty(order = 1, isRequire = true)
	public com.pxhua.video.proto.commondef.st_user_info user_info = null;
	@TarsStructProperty(order = 2, isRequire = true)
	public java.util.Map<String, String> cookie = null;
	@TarsStructProperty(order = 3, isRequire = true)
	public int platform = 0;
	@TarsStructProperty(order = 4, isRequire = true)
	public int client_type = 0;

	public int getToken_mode() {
		return token_mode;
	}

	public void setToken_mode(int token_mode) {
		this.token_mode = token_mode;
	}

	public com.pxhua.video.proto.commondef.st_user_info getUser_info() {
		return user_info;
	}

	public void setUser_info(com.pxhua.video.proto.commondef.st_user_info user_info) {
		this.user_info = user_info;
	}

	public java.util.Map<String, String> getCookie() {
		return cookie;
	}

	public void setCookie(java.util.Map<String, String> cookie) {
		this.cookie = cookie;
	}

	public int getPlatform() {
		return platform;
	}

	public void setPlatform(int platform) {
		this.platform = platform;
	}

	public int getClient_type() {
		return client_type;
	}

	public void setClient_type(int client_type) {
		this.client_type = client_type;
	}

	public st_login_verify_req() {
	}

	public st_login_verify_req(int token_mode, com.pxhua.video.proto.commondef.st_user_info user_info, java.util.Map<String, String> cookie, int platform, int client_type) {
		this.token_mode = token_mode;
		this.user_info = user_info;
		this.cookie = cookie;
		this.platform = platform;
		this.client_type = client_type;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + TarsUtil.hashCode(token_mode);
		result = prime * result + TarsUtil.hashCode(user_info);
		result = prime * result + TarsUtil.hashCode(cookie);
		result = prime * result + TarsUtil.hashCode(platform);
		result = prime * result + TarsUtil.hashCode(client_type);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (!(obj instanceof st_login_verify_req)) {
			return false;
		}
		st_login_verify_req other = (st_login_verify_req) obj;
		return (
			TarsUtil.equals(token_mode, other.token_mode) &&
			TarsUtil.equals(user_info, other.user_info) &&
			TarsUtil.equals(cookie, other.cookie) &&
			TarsUtil.equals(platform, other.platform) &&
			TarsUtil.equals(client_type, other.client_type) 
		);
	}

	public void writeTo(TarsOutputStream _os) {
		_os.write(token_mode, 0);
		_os.write(user_info, 1);
		_os.write(cookie, 2);
		_os.write(platform, 3);
		_os.write(client_type, 4);
	}

	static com.pxhua.video.proto.commondef.st_user_info cache_user_info;
	static { 
		cache_user_info = new com.pxhua.video.proto.commondef.st_user_info();
	}
	static java.util.Map<String, String> cache_cookie;
	static { 
		cache_cookie = new java.util.HashMap<String, String>();
		String var_1 = "";
		String var_2 = "";
		cache_cookie.put(var_1 ,var_2);
	}

	public void readFrom(TarsInputStream _is) {
		this.token_mode = _is.read(token_mode, 0, true);
		this.user_info = (com.pxhua.video.proto.commondef.st_user_info) _is.read(cache_user_info, 1, true);
		this.cookie = (java.util.Map<String, String>) _is.read(cache_cookie, 2, true);
		this.platform = _is.read(platform, 3, true);
		this.client_type = _is.read(client_type, 4, true);
	}

}
