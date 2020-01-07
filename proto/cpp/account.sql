create table `t_account`
(
	`uid` BIGINT PRIMARY KEY AUTO_INCREAMENT, -- set start id
	`user_type` smallint NOT NULL,
	`user_id` varchar(64), -- unionid if wx
	--`appid` varchar(32),
	`nick_name` varchar(64),
	`avatar` text,
	`is_main` smallint DEFAULT 1,
	`main_uid` bigint,
	index userid (user_id, main_uid)
);
