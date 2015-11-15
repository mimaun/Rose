-- Create and populate the table of usernames and passwords for the 
--        login-logout-count example.  Adapted from code at 2my4edge.com
--        by Claude Anderson for CSSE 280/290 at Rose-Hulman.


CREATE DATABASE IF NOT EXISTS login_logout; 
USE login_logout;

CREATE TABLE IF NOT EXISTS login (
  id int(11) NOT NULL AUTO_INCREMENT,
  name varchar(25) NOT NULL,
  password varchar(25) NOT NULL,
  visits int(5) NOT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY name (name)
) AUTO_INCREMENT=28 ;

INSERT IGNORE INTO login (id, name, password, visits) VALUES
	(1, 'tom', 'tom', 0),
	(11, 'huck', 'huck', 0),
	(15, 'sid', 'sid', 0),
	(16, 'jim', 'jim', 0),
	(18, 'becky', 'becky', 0),
	(20, 'aunt polly', 'aunt polly', 0);


