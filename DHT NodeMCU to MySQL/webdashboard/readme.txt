SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+07:00";

CREATE TABLE temperature_db (
    id INT(11) NOT NULL AUTO_INCREMENT,
    temperature FLOAT NOT NULL,
    humidity FLOAT NOT NULL,
    create_date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

โค้ดนี้เป็นคำสั่ง SQL ที่ทำหน้าที่สร้างตารางสำหรับฐานข้อมูล โดยโค้ดนี้ประกอบด้วยรายละเอียดดังนี้:

### 1. `SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";`
- คำสั่งนี้กำหนดค่า `SQL_MODE` เพื่อให้ระบบไม่เพิ่มค่าอัตโนมัติ (`AUTO_INCREMENT`) สำหรับค่า `0` ในคอลัมน์ที่มี `AUTO_INCREMENT` ถ้าหากคอลัมน์นั้นกำหนดค่าเป็น `0` จะไม่ถูกนับเป็นค่าเริ่มต้นในการเพิ่มค่าอัตโนมัติ

### 2. `SET time_zone = "+07:00";`
- คำสั่งนี้กำหนด Time Zone ของระบบเป็น `+07:00` ซึ่งเป็นเวลาในประเทศไทย (เช่น Bangkok Standard Time)

### 3. คำสั่งสร้างตาราง `CREATE TABLE temperature_db`
- คำสั่งนี้ทำการสร้างตารางชื่อ `temperature_db` ซึ่งมีคอลัมน์และโครงสร้างตามรายละเอียดด้านล่าง:

### 4. คอลัมน์ในตาราง
- `id INT(11) NOT NULL AUTO_INCREMENT`: คอลัมน์ `id` ใช้ประเภทข้อมูลเป็น `INT` ขนาด 11 หลัก, ไม่สามารถมีค่าเป็น `NULL`, และจะเพิ่มค่าอัตโนมัติ (`AUTO_INCREMENT`) ทุกครั้งเมื่อมีการเพิ่มข้อมูลใหม่
- `temperature FLOAT NOT NULL`: คอลัมน์ `temperature` เก็บข้อมูลอุณหภูมิในรูปแบบ `FLOAT` และต้องมีค่าเสมอ (ไม่สามารถเป็น `NULL`)
- `humidity FLOAT NOT NULL`: คอลัมน์ `humidity` เก็บข้อมูลความชื้นในรูปแบบ `FLOAT` และต้องมีค่าเสมอ (ไม่สามารถเป็น `NULL`)
- `create_date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP`: คอลัมน์ `create_date` ใช้ประเภทข้อมูล `TIMESTAMP` และจะบันทึกเวลาเป็นค่าเริ่มต้นเมื่อมีการเพิ่มข้อมูล (ค่าเริ่มต้นเป็น `CURRENT_TIMESTAMP`) และจะอัปเดตเวลาทุกครั้งเมื่อมีการเปลี่ยนแปลงข้อมูล (`ON UPDATE CURRENT_TIMESTAMP`)

### 5. กำหนด `PRIMARY KEY`
- `PRIMARY KEY (id)`: กำหนดให้คอลัมน์ `id` เป็น `Primary Key` ซึ่งทำหน้าที่เป็นตัวระบุเอกลักษณ์ของแต่ละแถวในตาราง

### 6. `ENGINE=InnoDB DEFAULT CHARSET=utf8mb4`
- กำหนดให้ตารางใช้ `InnoDB` เป็น Storage Engine และใช้ชุดตัวอักษร `utf8mb4` ซึ่งรองรับการเก็บข้อมูลที่เป็น Unicode เช่น อักขระภาษาไทยหรือ Emoji

### โดยสรุป
โค้ดนี้สร้างตารางชื่อ `temperature_db` เพื่อเก็บข้อมูลอุณหภูมิและความชื้น โดยใช้คอลัมน์ `id` เป็น `Primary Key` และบันทึกวันที่และเวลาที่ข้อมูลถูกเพิ่มหรืออัปเดตในคอลัมน์ `create_date`