--function keyPress(key)
--    print("keyPress", key)
--end

--function keyRelease(key)
--    print("keyRelease", key)
--end

function mousePress(button, x, y)
    rx, ry, rz, dx, dy, dz = Camera.GetRay(x, y)
	hit, hx, hy, hz = Physics.Raycast(rx, ry, rz, dx, dy, dz)
	if (hit == nil) then
		return
	end
	print(GameObject.GetName(Component.GetGameObject(hit)), hx, hy, hz)
end

--function mouseRelease(button, x, y)
--    print("mouseRelease", button, x, y)
--end

--function mouseMove(x, y)
--    print("mouseMove", x, y)
--end

--function wheel(delta)
--    print("wheel", delta)
--end