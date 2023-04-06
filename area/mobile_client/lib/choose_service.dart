import 'package:flutter/material.dart';
import 'select_action_page.dart';
import 'dart:convert';
import 'services_class.dart';
import 'package:http/http.dart' as http;

class ChooseService extends StatefulWidget {
  const ChooseService({Key? key}) : super(key: key);
  static const routeName = '/ChooseService';

  @override
  State<ChooseService> createState() => _ChooseServiceState();
}

Future<ServicesList> readJson() async {
  final response =
      await http.get(Uri.parse('http://10.0.2.2:8080/api/service'));
  if (response.statusCode == 200) {
    final data = await json.decode(response.body);
    ServicesList services = ServicesList.fromJson(data['services']);
    return (services);
  } else {
    return Future.error("Error when fetching services, please try again");
  }
}

class _ChooseServiceState extends State<ChooseService> {
  @override
  Widget build(BuildContext context) {
    final comeFrom = ModalRoute.of(context)!.settings.arguments as bool;
    return Scaffold(
      appBar: AppBar(
        iconTheme: const IconThemeData(
          color: Colors.black, //change your color here
        ),
        backgroundColor: Colors.white,
        centerTitle: true,
        title: const Text('Choose a service',
            style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold)),
      ),
      backgroundColor: const Color(0xffffffff),
      body: FutureBuilder<ServicesList>(
          future: readJson(),
          builder: (context, snapshot) {
            if (snapshot.hasError) {
              return const Center(
                child: Text('Error when fetching services, please try again.'),
              );
            } else if (snapshot.hasData) {
              return RenderServicesList(
                  services: snapshot.data!, comeFrom: comeFrom);
            } else {
              return const Center(
                child: CircularProgressIndicator(),
              );
            }
          }),
    );
  }
}

class RenderServicesList extends StatefulWidget {
  final bool comeFrom;
  const RenderServicesList(
      {Key? key, required this.services, required this.comeFrom})
      : super(key: key);

  final ServicesList services;
  @override
  State<RenderServicesList> createState() => _RenderServicesListState();
}

class _RenderServicesListState extends State<RenderServicesList> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: const Color(0xffffffff),
        body: SafeArea(
            child: Center(
                child: Column(
          children: <Widget>[
            const SizedBox(
              height: 10,
            ),
            SizedBox(
              height: MediaQuery.of(context).size.height * 0.8,
              child: GridView.builder(
                gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                    crossAxisCount: 2),
                itemBuilder: _buildServicesItem,
                itemCount: widget.services.services.length,
              ),
            ),
          ],
        ))));
  }

  Widget _buildServicesItem(BuildContext context, int index) {
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
          Navigator.pushNamed(context, SelectActionPage.routeName,
                  arguments:
                      ChooseServiceDB(index, widget.comeFrom, widget.services))
              .then((_) => setState(() {}));
        },
        child: Container(
          color: Colors.white,
          width: 200,
          height: 200,
          child: Center(
            child: Text(widget.services.services[index].name,
                textAlign: TextAlign.center,
                style: const TextStyle(
                    color: Colors.black,
                    fontWeight: FontWeight.bold,
                    fontSize: 25)),
          ),
        ),
      ),
    );
  }
}
