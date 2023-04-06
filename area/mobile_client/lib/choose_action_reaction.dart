import 'package:area/choose_service.dart';
import 'package:area/homepage.dart';
import 'package:area/recap_action_page.dart';
import 'package:flutter/material.dart';

class ChooseActionReaction extends StatefulWidget {
  const ChooseActionReaction({Key? key}) : super(key: key);
  static const routeName = '/ChooseActionReaction';

  @override
  State<ChooseActionReaction> createState() => _ChooseActionReactionState();
}

class _ChooseActionReactionState extends State<ChooseActionReaction> {
  void checkButtonState() {
    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        iconTheme: const IconThemeData(
          color: Colors.black, //change your color here
        ),
        //automaticallyImplyLeading: false,
        backgroundColor: Colors.white,
        centerTitle: true,
        title: const Text('Create your own', style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold)),
      ),
      backgroundColor: const Color(0xffffffff),
      body: SafeArea(
        child: Center(
          child: Column(
            children: <Widget>[
              const SizedBox(
                height: 70,
              ),
              ElevatedButton(
                  child: areaToJson.checkIfActionIsNull()
                      ? const Text('If This')
                      : Text("If ${areaToJson.currentAction!.name}"),
                  style: ElevatedButton.styleFrom(
                      minimumSize: Size(MediaQuery.of(context).size.width * 0.90, 75),
                      primary: Colors.black,
                      textStyle: const TextStyle(fontSize: 30, fontWeight: FontWeight.bold)),
                  onPressed: () {
                    Navigator.pushNamed(
                      context,
                      ChooseService.routeName,
                      arguments: false,
                    ).then((_) => setState(() {}));
                  }),
              Container(height: 20, width: 4, decoration: const BoxDecoration(color: Color(0xffdcdcdc))),
              ElevatedButton(
                  child: areaToJson.checkIfReactionIsNull()
                      ? const Text('Then That')
                      : Text("Then ${areaToJson.currentReaction!.name}"),
                  style: ElevatedButton.styleFrom(
                      minimumSize: Size(MediaQuery.of(context).size.width * 0.90, 75),
                      primary: areaToJson.checkIfActionIsNull() ? Colors.grey : Colors.black,
                      textStyle: const TextStyle(fontSize: 30, fontWeight: FontWeight.bold)),
                  onPressed: () {
                    if (areaToJson.checkIfActionIsNull()) return;
                    Navigator.pushNamed(
                      context,
                      ChooseService.routeName,
                      arguments: true,
                    ).then((_) => setState(() {}));
                  }),
              const SizedBox(
                height: 200,
              ),
              if (areaToJson.currentAction != null && areaToJson.currentReaction != null)
                ElevatedButton(
                    child: const Text('Continue'),
                    style: ElevatedButton.styleFrom(
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(30.0),
                        ),
                        minimumSize: Size(MediaQuery.of(context).size.width * 0.90, 75),
                        primary: Colors.black,
                        textStyle: const TextStyle(fontSize: 30, fontWeight: FontWeight.bold)),
                    onPressed: () {
                      if (areaToJson.checkIfActionIsNull()) return;
                      Navigator.pushNamed(
                        context,
                        RecapActionPage.routeName,
                      ).then((_) => setState(() {}));
                    }),
            ],
          ),
        ),
      ),
    );
  }
}
