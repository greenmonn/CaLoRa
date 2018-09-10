# Configure Arduino IDE

- Preference에서 Additional Board Manager URL에 다음 json 파일 추가
    * http://www.dragino.com/downloads/downloads/YunShield/package_dragino_yun_test_index.json
- Board Manager에서 `Dragino Yun` Package 설치
- Tools - Board에서 Dragino Yun + UNO 선택
- MCU(Microcontroller Unit)에 업로드하기
    * LG01 게이트웨이 네트워크에 연결
    * Network ports에서 내부 네트워크에 접속
        ```
        Private IP Addresses

        192.168.0.0 - 192.168.255.255 (65,536 IP addresses)
        172.16.0.0 - 172.31.255.255 (1,048,576 IP addresses)
        10.0.0.0 - 10.255.255.255 (16,777,216 IP addresses)
        ```

    * 코드 컴파일 후 네트워크 포트로 업로드한다.
        - 업로드 시 비밀번호를 요구하는데, 초기 비밀번호는 `dragino`이다. (게이트웨이 설정 페이지에서 바꿀 수 있다.)