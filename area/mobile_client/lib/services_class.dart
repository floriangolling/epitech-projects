import 'actions_class.dart';
import 'reactions_class.dart';

class ServicesList {
  final List<Services> services;

  ServicesList({
    required this.services,
  });

  factory ServicesList.fromJson(List<dynamic> parsedJson) {
    List<Services> services = <Services>[];
    services = parsedJson.map((i) => Services.fromJson(i)).toList();
    return ServicesList(services: services);
  }
}

class Services {
  Services({
    required this.name,
    required this.actions,
    required this.reactions,
  });
  final String name;
  final List<Actions> actions;
  final List<Reactions> reactions;

  factory Services.fromJson(Map<String, dynamic> data) {
    final name = data['name'] as String?;
    if (name == null) {
      throw UnsupportedError('Invalid data: $data -> "name" is missing');
    }
    final actionsData = data['actions'] as List<dynamic>?;
    final actions =
        actionsData != null ? actionsData.map((actionsData) => Actions.fromJson(actionsData)).toList() : <Actions>[];
    final reactionsData = data['reactions'] as List<dynamic>?;
    final reactions = reactionsData != null
        ? reactionsData.map((reactionsData) => Reactions.fromJson(reactionsData)).toList()
        : <Reactions>[];
    return Services(name: name, actions: actions, reactions: reactions);
  }
}

class ChooseServiceDB {
  final int index;
  final bool comeFrom;
  final ServicesList services;
  ChooseServiceDB(this.index, this.comeFrom, this.services);
}
