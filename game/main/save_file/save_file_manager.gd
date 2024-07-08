extends Node
class_name SaveFileManager

# Manages save files

var files: Array[SaveFile] = []

func _ready() -> void:
	update_files()

func update_files() -> void:
	files.clear()
	var dir: DirAccess = DirAccess.open("user://")
	for folder in dir.get_directories():
		if not folder.begins_with("save"):
			continue
		
		var res: SaveFile = ResourceLoader.load("%s/%s/res.tres" % [dir.get_current_dir(), folder])
		var img_file: FileAccess = FileAccess.open("%s/%s/img.png" % [dir.get_current_dir(), folder], FileAccess.READ)
		res.size = img_file.get_length()
		res.thumbnail = load_thumbnail("%s/%s/thumbnail.png" % [dir.get_current_dir(), folder], res.version)
		
		files.append(res)

func create_save_file(save_name: String) -> SaveFile:
	var cleaned_name: String = ""
	for c in save_name:
		if c == " ":
			c = "_"
		# Regex would be nice here, but there's no strict match method so I'd rather not mess with it
		if not c in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_":
			continue
		cleaned_name += c.to_lower()
	if len(cleaned_name) == 0:
		cleaned_name = "new_file" + str(randi() % 1000)
	save_name = cleaned_name
	
	var date: Dictionary = Time.get_datetime_dict_from_system(true)
	var date_string: String = Time.get_datetime_string_from_datetime_dict(date, false)
	var folder_name: String = "save_" + save_name + "_" + date_string
	folder_name = folder_name.replace(":", "_")
	var dir: DirAccess = DirAccess.open("user://")
	dir.make_dir(folder_name)
	
	var file = SaveFile.new()
	file.save_name = save_name
	file.date = date_string
	file.time_created = int(Time.get_unix_time_from_system())
	file.version = ProjectSettings.get_setting("application/config/version")
	
	save_image("user://" + folder_name + "/img.png")
	save_thumbnail("user://" + folder_name + "/thumbnail.png")
	ResourceSaver.save(file, "user://" + folder_name + "/res.tres")
	
	update_files()
	
	return file

func overwrite_save_file(file: SaveFile) -> void:
	var path: String = file.get_path()
	var folder: String = path.substr(0, path.rfind("/") + 1)
	save_image(folder + "/img.png")
	save_thumbnail(folder + "/thumbnail.png")
	file.version = ProjectSettings.get_setting("application/config/version")
	ResourceSaver.save(file, path)
	
	update_files()

func load_from_file(file: SaveFile) -> void:
	var path: String = file.get_path()
	var folder: String = path.substr(0, path.rfind("/") + 1)
	var resource: SaveFile = ResourceLoader.load(folder + "/res.tres")
	
	load_image(folder + "/img.png", resource.version)

func delete_save_file(file: SaveFile) -> void:
	var path: String = file.get_path()
	var folder: String = path.substr(0, path.rfind("/") + 1)
	var dir: DirAccess = DirAccess.open(folder)
	dir.remove(path)
	dir.remove(folder + "img.png")
	dir.remove(folder + "thumbnail.png")
	dir.remove("")
	files.remove_at(files.find(file))
	
	update_files()

func save_image(path: String) -> void:
	var sim: SandSimulation = CommonReference.main.sim
	
	var image: Image = Image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_RGBA8, CommonReference.main.sim.get_data())
	image.save_png(path)

func save_thumbnail(path: String) -> void:
	var sim: SandSimulation = CommonReference.main.sim
	
	var image: Image = Image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_RGB8, CommonReference.main.sim.get_color_image(false))
	image.save_png(path)

func load_image(path: String, version: String) -> void:
	var sim: SandSimulation = CommonReference.main.sim
	
	CommonReference.painter.clear()
	if version.begins_with("4"):
		var img: Image = Image.load_from_file(path)
		for i in range(sim.get_height()):
			for j in range(sim.get_width()):
				if j >= img.get_width() or i >= img.get_height():
					continue
				CommonReference.main.sim.set_cell(i, j, img.get_pixel(j, i).to_rgba32())
	else:
		# Loading files before the limit increase
		var img: Image = Image.load_from_file(path)
		for i in range(CommonReference.main.sim.get_height()):
			for j in range(CommonReference.main.sim.get_width()):
				if j >= img.get_width() or i >= img.get_height():
					continue
				var id: int = int(255 * img.get_pixel(j, i).r)
				# Taps now start from 4097
				if id >= 128:
					id -= 128
					id += 4097
				CommonReference.main.sim.set_cell(i, j, id)
	CommonReference.canvas.repaint()

func load_thumbnail(path: String, version: String) -> Resource:
	if version.begins_with("4"):
		var img: Image = Image.load_from_file(path)
		return img
	return Image.new()
