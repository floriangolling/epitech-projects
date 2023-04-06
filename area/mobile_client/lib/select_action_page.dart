import 'package:area/homepage.dart';
import 'package:area/services_class.dart';
import 'package:flutter/material.dart';

// ignore: must_be_immutable
class SelectActionPage extends StatefulWidget {
  static const routeName = '/SelectActionPage';
  late ChooseServiceDB choosenService;

  SelectActionPage({Key? key}) : super(key: key);

  @override
  State<SelectActionPage> createState() => _SelectActionPageState();
}

class _SelectActionPageState extends State<SelectActionPage> {
  @override
  Widget build(BuildContext context) {
    final args = ModalRoute.of(context)!.settings.arguments as ChooseServiceDB;
    widget.choosenService = args;
    return Scaffold(
      appBar: AppBar(
        iconTheme: const IconThemeData(
          color: Colors.black,
        ),
        backgroundColor: Colors.white,
        centerTitle: true,
        title: Text('Triggers for ${args.services.services[args.index].name} service',
            style: const TextStyle(color: Colors.black)),
      ),
      backgroundColor: const Color(0xffffffff),
      body: SafeArea(
        child: Center(
          child: Column(
            children: <Widget>[
              const SizedBox(
                height: 5,
              ),
              SizedBox(
                height: MediaQuery.of(context).size.height * 0.8,
                child: ListView.builder(
                  itemCount: args.comeFrom == false
                      ? args.services.services[args.index].actions.length
                      : args.services.services[args.index].reactions.length,
                  itemBuilder: _buildServcicesActions,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }

  Widget _buildServcicesActions(BuildContext context, int index) {
    return Card(
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(20), // if you need this
        side: BorderSide(
          color: Colors.grey.withOpacity(0.3),
          width: 1,
        ),
      ),
      child: InkWell(
        onTap: () {
          widget.choosenService.comeFrom == false
              ? areaToJson.currentAction =
                  widget.choosenService.services.services[widget.choosenService.index].actions[index]
              : areaToJson.currentReaction =
                  widget.choosenService.services.services[widget.choosenService.index].reactions[index];
          int count = 0;
          Navigator.popUntil(context, (route) {
            return count++ == 2;
          });
        },
        child: Container(
          color: Colors.white,
          width: 200,
          height: 200,
          child: Center(
            child: Text(
                widget.choosenService.comeFrom == false
                    ? widget.choosenService.services.services[widget.choosenService.index].actions[index].description
                    : widget.choosenService.services.services[widget.choosenService.index].reactions[index].description,
                textAlign: TextAlign.center,
                style: const TextStyle(color: Colors.black, fontWeight: FontWeight.bold, fontSize: 25)),
          ),
        ),
      ),
    );
  }
}
