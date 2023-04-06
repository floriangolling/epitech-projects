import 'package:area/homepage.dart';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';
import 'login_screen.dart';
import 'end_session.dart';

class RecapActionPage extends StatefulWidget {
  const RecapActionPage({Key? key}) : super(key: key);
  static const routeName = '/RecapActionPage';

  @override
  State<RecapActionPage> createState() => _RecapActionPageState();
}

class _RecapActionPageState extends State<RecapActionPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          iconTheme: const IconThemeData(
            color: Colors.black,
          ),
          backgroundColor: Colors.white,
          centerTitle: true,
          title: const Text('Review and Finish',
              style: TextStyle(color: Colors.black)),
        ),
        backgroundColor: const Color(0xffffffff),
        body: SafeArea(
            child: Center(
                child: Column(
          children: <Widget>[
            const SizedBox(
              height: 100,
            ),
            SizedBox(
              height: 25.0,
              width: MediaQuery.of(context).size.width * 0.80,
              child: const Text('   Applet name',
                  style: TextStyle(
                      color: Colors.black,
                      fontSize: 20,
                      fontWeight: FontWeight.bold)),
            ),
            Container(
                height: 150,
                width: MediaQuery.of(context).size.width * 0.80,
                padding: const EdgeInsets.all(5.0),
                decoration: ShapeDecoration(
                    color: Colors.white,
                    shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(10.0),
                        side: const BorderSide(width: 2, color: Colors.black))),
                child: Center(
                    child: SingleChildScrollView(
                  scrollDirection: Axis.vertical,
                  child: Text(
                      'If ' +
                          areaToJson.currentAction!.description +
                          ', then ' +
                          areaToJson.currentReaction!.description,
                      style:
                          const TextStyle(color: Colors.black, fontSize: 20)),
                ))),
            const SizedBox(
              height: 50,
            ),
            ElevatedButton(
                child: const Text('Finish'),
                style: ElevatedButton.styleFrom(
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(30.0),
                    ),
                    minimumSize:
                        Size(MediaQuery.of(context).size.width * 0.80, 75),
                    primary: Colors.black,
                    textStyle: const TextStyle(
                        fontSize: 30, fontWeight: FontWeight.bold)),
                onPressed: () async {
                  if (areaToJson.checkIfActionIsNull()) return;
                  final response = await execPost();
                  if (response == true) {
                    Navigator.of(context)
                        .pushNamedAndRemoveUntil(
                            '/', (Route<dynamic> route) => false)
                        .then((_) => setState(() {}));
                  }
                }),
          ],
        ))));
  }

  Future<bool> execPost() async {
    final token = await storage.read(key: 'area-token');
    final response = await http.post(
      Uri.parse('http://10.0.2.2:8080/api/component'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
        'authorization': 'Bearer $token',
      },
      body: jsonEncode(<String, String>{
        'serviceReactionName': areaToJson.currentReaction!.serviceName,
        "serviceActionName": areaToJson.currentAction!.serviceName,
        "actionName": areaToJson.currentAction!.name,
        "reactionName": areaToJson.currentReaction!.name,
      }),
    );
    if (response.statusCode == 200) {
      return (true);
    } else if (response.statusCode == 403) {
      EndSession(context);
      return (false);
    } else {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
        content: Text("An error occured, please try again"),
      ));
      return (false);
    }
  }
}
